#include "Player.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "PlayerTornado.h"
#include "../Components/Animator.h"
#include "../Components/Collider3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "../Objects/DebugGround.h"
#include "Collision/Collision3D.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Math.h"

#include "System/Input/Keyboard.h"

namespace
{
	const char* const kPlayerParamPath = "Resource\\MasterData\\PlayerParam.csv";

	const char* const kAABBParamPath = "Resource\\MasterData\\PlayerAABBColliderParam.csv";

	const char* const kModelHandlePath = "Resource\\Model\\Hero.x";
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
	mModel(nullptr),
	mAnimator(nullptr),
	mTornado(nullptr)
{
	SetTag(Tag::Player);

	mParam = Data::Csv::LoadCsvAs<PlayerParam>(kPlayerParamPath)[0];

	mModel = std::make_unique<ModelRenderer>(this);
	mModel->Load(kModelHandlePath);
	mModel->DisableMovement("root");

	mAnimator = std::make_unique<Animator>(mModel.get(), 30.0f);

	mTornado = AddToChild<PlayerTornado>(bulletManager);

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

	MoveHorizontal(deltaTime);
	MoveVertical(deltaTime);

	if (InputManager::GetInstance().IsPressed(Input::Action::Spin))
	{
		mTornado->SetSpinningFlag(true);
	}
	if (InputManager::GetInstance().IsReleased(Input::Action::Spin))
	{
		mTornado->CreateBullet(mLastMoveVec);

		mTornado->SetSpinningFlag(false);
	}

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

		ImGui::Text("CanJumpTimer: %f", mCanJumpTimer);
		ImGui::Text("StickWallCancelTimer: %f", mStickWallCancelTimer);

		ImGui::Text("IsJumping: %d", mIsJumping);
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
		
		// 地面との衝突
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

		// 壁との衝突
		mOnWall = true;

		return;
	}

	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:
		mCollisionPush += result.normal * result.penetration;

		mLastCollideNormal = result.normal;

		// TODO: 壁ジャンプと同時に壁と反対に入力すると壁に向かって壁ジャンプするバグ修正
		
		// 壁との衝突
		if (!Math::IsNearZero(result.normal.x))
		{
			mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			mVelocity.z = 0.0f;
		}

		// 地面との衝突
		if (result.normal.y > 0.5f)
		{
			mVelocity.y = Math::Max(mVelocity.y, 0.0f);
		}
		// 天井との衝突
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

void Player::MoveHorizontal(float deltaTime)
{
	if (mIgnoreMoveInputTimer > 0.0f) return;

	// 水平方向の移動
	Vector3 moveVec = InputManager::GetInstance().GetAsVector3(Input::Action::Move);

	// ダッシュ
	float moveCoef = 1.0f;
	if (InputManager::GetInstance().IsDown(Input::Action::Dash))
	{
		moveCoef *= mParam.dashCoef;
	}

	// カメラを正面に移動
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	moveVec = right * moveVec.x + forward * moveVec.z;

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;

	float accelCoef = mOnGround ? 1.0f : mParam.airResistanceCoef;

	if (mOnWall)
	{
		Vector3 vec = mLastCollideNormal;
		std::swap(vec.x, vec.z);

		// 壁と逆方向に入力していたらタイマーをカウントアップ
		vec.z = -vec.z;
		Vector3 inputVec = moveVec.Cross(vec);
		if (inputVec.y > mParam.stickWallCancelMoveVectorThreshold)
		{
			mStickWallCancelTimer += deltaTime;

			moveVec = Vector3::Zero;
		}
		// 壁と逆方向に入力されていなかったらタイマーリセット
		else
		{
			mStickWallCancelTimer = 0.0f;
		}
		// 壁ずりキャンセル
		if (mStickWallCancelTimer > mParam.stickWallCancelTimeThreshold)
		{
			mStickWallCancelTimer = 0.0f;
			mOnWall = false;
			mOnCancelStickWall = true;
		}
		
		// 壁ずり状態なら壁に沿って移動させる
		moveVec = vec * moveVec.Dot(vec);
	}

	mVelocity.x = Math::Approach(mVelocity.x, mParam.walkSpeed * moveCoef * moveVec.x, mParam.walkAccel * accelCoef);
	mVelocity.z = Math::Approach(mVelocity.z, mParam.walkSpeed * moveCoef * moveVec.z, mParam.walkAccel * accelCoef);
}

void Player::MoveVertical(float deltaTime)
{
	// ジャンプ
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && CanJump())
	{
		mVelocity.y = mParam.jumpForce;
		mIsJumping = true;
		mCanJumpTimer = 0.0f;

		// 壁ジャンプ
		if (mOnWall && !mOnGround)
		{
			mVelocity = mLastCollideNormal * mParam.wallJumpHorizontalForce;
			mVelocity.y = mParam.wallJumpVerticalForce;
			mLastMoveVec = mLastCollideNormal;

			mIgnoreMoveInputTimer = mParam.wallJumpIgnoreMoveInputTime;

			mOnWall = false;
		}
	}
	// ジャンプキャンセル
	if (InputManager::GetInstance().IsReleased(Input::Action::Jump) && CanCancelJump())
	{
		mVelocity.y = mParam.jumpCancelThreshold;
		mIsJumping = false;
	}

	// 落下処理
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
