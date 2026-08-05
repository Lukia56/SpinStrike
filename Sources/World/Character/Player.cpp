#include "Player.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "PlayerTornado.h"
#include "../Component/ModelAnimator.h"
#include "../Component/Collider3D.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "../Object/DebugGround.h"
#include "Collision/Collision3D.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Math.h"

#include "System/Input/Keyboard.h"

namespace
{
	const char* const kPlayerParamPath = "Resources\\MasterData\\PlayerParam.csv";

	const char* const kAABBParamPath = "Resources\\MasterData\\PlayerAABBColliderParam.csv";

	const char* const kModelHandlePath = "Resources\\Model\\Hero.x";

	constexpr float kSpinStartTime = 0.5f;
	constexpr float kSpinCooldownTime = 1.0f;


	constexpr float kSpinStaminaTime = 5.0f;
}

Player::Player(PlayerBulletManager* bulletManager) :
	mLastMoveVec(Vector3::XAxis),
	mCanJumpTimer(0.0f),
	mIsJumping(false),
	mOnGround(false),
	mOnWall(false),
	mOnCancelStickWall(false),
	mStickWallCancelTimer(0.0f),
	mIgnoreMoveInputTimer(0.0f),
	mIsSpinning(false),
	mSpinStamina(kSpinStaminaTime),
	mSpinStartTimer(0.0f),
	mSpinCooldownTimer(0.0f),
	mModel(nullptr),
	mAnimator(nullptr),
	mTornado(nullptr)
{
	SetTag(Tag::Player);

	mParam = Data::Csv::LoadCsvAs<PlayerParam>(kPlayerParamPath)[0];

	mModel = std::make_unique<ModelRenderer>(this);
	mModel->Load(kModelHandlePath);
	mModel->DisableMovement("root");

	mAnimator = std::make_unique<ModelAnimator>(mModel.get(), 30.0f);

	mTornado = AddToChild<PlayerTornado>(bulletManager);
	mTornado->SetActive(false);

	auto aabbParam = Data::Csv::LoadCsvAs<AABBColliderParam>(kAABBParamPath);
	for (const auto& param : aabbParam)
	{
		mColliders.emplace_back(
			std::make_unique<Collider3D>(
				std::make_unique<Collision::AABB3D>(param.size, param.offsetPos),
				this,
				param.collisionTag
			));
	}

	AddToChild<DebugGround>();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Finalize()
{
}

void Player::Update()
{
	float deltaTime = TimeManager::GetDeltaTime();

	mOnCancelStickWall = false;

	ResolvePush();

	SpinAction(deltaTime);
	MoveHorizontal(deltaTime);
	MoveVertical(deltaTime);

	if (!mOnGround && mCanJumpTimer > 0.0f) mCanJumpTimer -= TimeManager::GetDeltaTime();

	if (mIgnoreMoveInputTimer > 0.0f) mIgnoreMoveInputTimer -= TimeManager::GetDeltaTime();

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_1)) mAnimator->Play(AnimationParam{ .animIndex = 0, .isLoop = true, .isForcePlay = false });
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_2)) mAnimator->Play(AnimationParam{ .animIndex = 1, .isLoop = true, .isForcePlay = true });

	mAnimator->Update();
}

void Player::PhysicsUpdate()
{
	mTransform.localPosition += mVelocity * TimeManager::GetDeltaTime();

	Vector3 worldPos = mTransform.CalculateWorldPosition();
	for (const auto& collider : mColliders)
	{
		collider->GetShape()->SetPosition(worldPos);
	}

	mOnGround = false;

	mOnWall = false;
}

void Player::Draw()
{
	Vector3 worldPos = mTransform.CalculateWorldPosition();

	mModel->Draw();

	DrawLine3D(worldPos.GetAsDxLibVector(), (worldPos + mLastMoveVec * 100.0f).GetAsDxLibVector(), Color::red.GetAsHexRGB());
}

void Player::DebugDraw()
{
	Vector3 pos = mTransform.CalculateWorldPosition();

	if (ImGui::Begin("Player"))
	{
		float posPtr[] = {pos.x, pos.y, pos.z};
		ImGui::InputFloat3("Position", posPtr, "%.1f");
		
		float velPtr[] = { mVelocity.x, mVelocity.y, mVelocity.z};
		ImGui::InputFloat3("Velocity", velPtr, "%.1f");

		float collPtr[] = { mLastCollideNormal.x, mLastCollideNormal.y, mLastCollideNormal.z };
		ImGui::InputFloat3("LastCollideNormal", collPtr, "%.1f");

		//ImGui::Text("CanJumpTimer: %f", mCanJumpTimer);
		//ImGui::Text("StickWallCancelTimer: %f", mStickWallCancelTimer);
		ImGui::Text("SpinStamina: %f", mSpinStamina);
		ImGui::Text("SpinCooldownTimer: %f", mSpinCooldownTimer);
		ImGui::Text("SpinStartTimer: %f", mSpinStartTimer);

		ImGui::Text("IsJumping: %d", mIsJumping);
		ImGui::Text("IsSpinning: %d", mIsSpinning);
		ImGui::Text("OnGround: %d", mOnGround);
		ImGui::Text("OnWall: %d", mOnWall);

		ImGui::End();
	}

	for (const auto& collider : mColliders)
	{
		collider->GetShape()->DebugDraw();
	}
}

void Player::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (myCollider->GetTag() == Collision::Tag::Foot)
	{
		if (oppCollider->GetOwner()->GetTag() != Tag::Terrain) return;

		if (result.normal.y < 0.0f || Math::IsNearZero(result.normal.y)) return;
		
		// ínñ Ç∆ÇÃè’ìÀ
		mCanJumpTimer = mParam.jumpBufferTime;
		mOnGround = true;
		mIsJumping = false;

		return;
	}
	else if (myCollider->GetTag() == Collision::Tag::CheckWall)
	{
		if (oppCollider->GetOwner()->GetTag() != Tag::Terrain) return;
		if (Math::IsNearZero(result.penetration)) return;
		if (mOnGround) return;
		if (mOnWall) return;
		if (mOnCancelStickWall) return;

		// ï«Ç∆ÇÃè’ìÀ
		mOnWall = true;

		return;
	}

	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:
		mCollisionPush += result.normal * result.penetration;

		mLastCollideNormal = result.normal;

		// TODO: ï«ÉWÉÉÉìÉvÇ∆ìØéûÇ…ï«Ç∆îΩëŒÇ…ì¸óÕÇ∑ÇÈÇ∆ï«Ç…å¸Ç©Ç¡Çƒï«ÉWÉÉÉìÉvÇ∑ÇÈÉoÉOèCê≥
		
		// ï«Ç∆ÇÃè’ìÀ
		if (!Math::IsNearZero(result.normal.x))
		{
			mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			mVelocity.z = 0.0f;
		}

		// ínñ Ç∆ÇÃè’ìÀ
		if (result.normal.y > 0.5f)
		{
			mVelocity.y = Math::Max(mVelocity.y, 0.0f);
		}
		// ìVà‰Ç∆ÇÃè’ìÀ
		if (result.normal.y < -0.5f)
		{
			mVelocity.y = Math::Min(mVelocity.y, 0.0f);
		}
		break;
	}
}

void Player::ResolvePush()
{
	if (mCollisionPush != Vector3::Zero)
	{
		mTransform.localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}

void Player::SpinAction(float deltaTime)
{
	if (mSpinCooldownTimer > 0.0f)
	{
		mSpinCooldownTimer -= deltaTime;
		return;
	}

	auto& input = InputManager::GetInstance();

	if (input.IsPressed(Input::Action::Spin))
	{
		mIsSpinning = true;

		mSpinStartTimer = kSpinStartTime;
	}

	if (mIsSpinning)
	{
		// ÔøΩgÔøΩÔøΩÔøΩlÔøΩ[ÔøΩhÔøΩÔøΩÔøΩNÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ
		if (!mTornado->IsActive())
		{
			if (mSpinStartTimer >= 0.0f)
			{
				mSpinStartTimer -= deltaTime;
			}
			else
			{
				mTornado->SetActive(true);
			}
		}
	
		// ÔøΩXÔøΩsÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ
		if (!input.IsDown(Input::Action::Spin))
		{
			mSpinStamina = kSpinStaminaTime;

			mIsSpinning = false;

			mSpinCooldownTimer = kSpinCooldownTime;

			mTornado->SetActive(false);
		}

		// ÔøΩXÔøΩ^ÔøΩ~ÔøΩiÔøΩÔøΩÔøΩJÔøΩEÔøΩÔøΩÔøΩgÔøΩÔøΩÔøΩÔøΩ
		if (mSpinStamina > 0.0f)
		{
			mSpinStamina -= deltaTime;
		}
		else
		{
			mSpinStamina = kSpinStaminaTime;

			mIsSpinning = false;

			mSpinCooldownTimer = kSpinCooldownTime;

			mTornado->SetActive(false);
		}
	}
}

void Player::MoveHorizontal(float deltaTime)
{
	if (mIgnoreMoveInputTimer > 0.0f) return;

	float targetSpeed = mParam.walkSpeed;
	float accel = mParam.walkAccel;

	if (InputManager::GetInstance().IsDown(Input::Action::Dash))
	{
		targetSpeed = mParam.dashSpeed;
		accel = mParam.dashAccel;
	}

	Vector3 moveVec = InputManager::GetInstance().GetAsVector3(Input::Action::Move);

	// ÉJÉÅÉâÇê≥ñ Ç…à⁄ìÆ
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	moveVec = right * moveVec.x + forward * moveVec.z;

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;

	if (mOnWall)
	{
		Vector3 vec = mLastCollideNormal;
		std::swap(vec.x, vec.z);

		// ï«Ç∆ãtï˚å¸Ç…ì¸óÕÇµÇƒÇ¢ÇΩÇÁÉ^ÉCÉ}Å[ÇÉJÉEÉìÉgÉAÉbÉv
		vec.z = -vec.z;
		Vector3 inputVec = moveVec.Cross(vec);
		if (inputVec.y > mParam.stickWallCancelMoveVectorThreshold)
		{
			mStickWallCancelTimer += deltaTime;

			moveVec = Vector3::Zero;
		}
		// ï«Ç∆ãtï˚å¸Ç…ì¸óÕÇ≥ÇÍÇƒÇ¢Ç»Ç©Ç¡ÇΩÇÁÉ^ÉCÉ}Å[ÉäÉZÉbÉg
		else
		{
			mStickWallCancelTimer = 0.0f;
		}
		// ï«Ç∏ÇËÉLÉÉÉìÉZÉã
		if (mStickWallCancelTimer > mParam.stickWallCancelTimeThreshold)
		{
			mStickWallCancelTimer = 0.0f;
			mOnWall = false;
			mOnCancelStickWall = true;
		}
		
		// ï«Ç∏ÇËèÛë‘Ç»ÇÁï«Ç…âàÇ¡Çƒà⁄ìÆÇ≥ÇπÇÈ
		moveVec = vec * moveVec.Dot(vec);
	}

	float accelCoef = mOnGround ? 1.0f : mParam.airResistanceCoef;

	// XÇ∆Zê¨ï™ÇæÇØï‚ä‘Ç≥ÇπÇÈ
	Vector3 vel = Vector3(mVelocity.x, 0.0f, mVelocity.z);
	vel = vel.Approach(moveVec * targetSpeed, accel * accelCoef);

	mVelocity.x = vel.x;
	mVelocity.z = vel.z;
}

void Player::MoveVertical(float deltaTime)
{
	// ÉWÉÉÉìÉv
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && CanJump())
	{
		mVelocity.y = mParam.jumpForce;
		mIsJumping = true;
		mCanJumpTimer = 0.0f;

		// ï«ÉWÉÉÉìÉv
		if (mOnWall && !mOnGround)
		{
			mVelocity = mLastCollideNormal * mParam.wallJumpHorizontalForce;
			mVelocity.y = mParam.wallJumpVerticalForce;
			mLastMoveVec = mLastCollideNormal;

			mIgnoreMoveInputTimer = mParam.wallJumpIgnoreMoveInputTime;

			mOnWall = false;
		}
	}
	// ÉWÉÉÉìÉvÉLÉÉÉìÉZÉã
	if (InputManager::GetInstance().IsReleased(Input::Action::Jump) && CanCancelJump())
	{
		mVelocity.y = mParam.jumpCancelThreshold;
		mIsJumping = false;
	}

	// óéâ∫èàóù
	if (!mOnGround)
	{
		if (mOnWall)
		{
			mVelocity.y = Math::Max(mVelocity.y - mParam.gravity * deltaTime, -mParam.stickWallFallSpeed);
		}
		else
		{
			mVelocity.y -= mParam.gravity * deltaTime;
		}
	}
}

bool Player::CanJump() const
{
	return mOnGround || mCanJumpTimer > 0.0f || mOnWall;
}

bool Player::CanCancelJump() const
{
	return mIsJumping && mVelocity.y > mParam.jumpCancelThreshold;
}
