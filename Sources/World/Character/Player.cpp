#include "Player.h"
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "PlayerTornado.h"
#include "../Component/ModelAnimator.h"
#include "../Component/Collider3D.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "../Other/BlobShadow.h"
#include "../Object/DebugGround.h"
#include "Collision/Collision3D.h"
#include "Param/Param.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "System/Resource/ResourceBase.h"
#include "Utility/Color.h"
#include "Utility/Math.h"

#include "System/Input/Keyboard.h"

namespace
{
	constexpr float kYawLatency = 0.25f;
}

Player::Player(std::shared_ptr<Resource::ResourceBase> model, std::shared_ptr<Resource::ResourceBase> shadowTexture, const PlayerParam& param, const std::vector<AABBColliderParam>& aabbParam, const PlayerInitData& initData, std::unique_ptr<PlayerTornado> tornado) :
	mLastMoveVec(Vector3::XAxis),
	mCanJumpTimer(0.0f),
	mIsJumping(false),
	mOnGround(false),
	mOnWall(false),
	mOnCancelStickWall(false),
	mStickWallCancelTimer(0.0f),
	mIgnoreMoveInputTimer(0.0f),
	mParam(param),
	mModel(nullptr),
	mAnimator(nullptr),
	mTornado(tornado.get())
{
	mTransform->localPosition = initData.transform.position;
	mTransform->localRotation = initData.transform.rotation;
	mTransform->localScale = initData.transform.scale;

	mModel = std::make_unique<ModelRenderer>(this, model);
	mModel->DisableMovement("root");

	CreateToChild<BlobShadow>(shadowTexture);

	AddToChild(std::move(tornado));

	for (const auto& param : aabbParam)
	{
		mColliders.emplace_back(
			std::make_unique<Collider3D>(
				std::make_unique<Collision::AABB3D>(param.size, param.offsetPos),
				this,
				param.collisionTag
			));
	}
}

Player::~Player()
{
}

void Player::Init()
{
	SetTag(Tag::Player);

	mAnimator = std::make_unique<ModelAnimator>(mModel.get(), 30.0f);

	CreateToChild<DebugGround>();
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

	// 角度を設定する
	if (mLastMoveVec != Vector3::Zero)
	{
		float targetYaw = std::atan2(mLastMoveVec.x, mLastMoveVec.z) + Math::kPi;
		float yawDiff = targetYaw - mTransform->CalculateWorldRotation().y;
		mTransform->localRotation.y += Math::NormalizeRadian(yawDiff) * kYawLatency;
	}

	if (!mOnGround && mCanJumpTimer > 0.0f) mCanJumpTimer -= deltaTime;

	if (mIgnoreMoveInputTimer > 0.0f) mIgnoreMoveInputTimer -= deltaTime;

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_1)) mAnimator->Play(AnimationParam{ .animIndex = 0, .isLoop = true, .isForcePlay = false });
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_2)) mAnimator->Play(AnimationParam{ .animIndex = 1, .isLoop = true, .isForcePlay = true });

	mAnimator->Update();
}

void Player::PhysicsUpdate()
{
	mTransform->localPosition += mVelocity * TimeManager::GetDeltaTime();

	for (const auto& collider : mColliders)
	{
		collider->Update();
	}

	mOnGround = false;

	mOnWall = false;
}

void Player::Draw()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mModel->Draw();

	DrawLine3D(worldPos.GetAsDxLibVector(), (worldPos + mLastMoveVec * 100.0f).GetAsDxLibVector(), Color::red.GetAsHexRGB());
}

void Player::DebugDraw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

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

		ImGui::Text("IsJumping: %d", mIsJumping);
		ImGui::Text("OnGround: %d", mOnGround);
		ImGui::Text("OnWall: %d", mOnWall);

		ImGui::End();
	}

	for (const auto& collider : mColliders)
	{
		collider->DebugDraw();
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

		// 押し出し量が多い成分だけ取得する
		Vector3 tempPush = result.normal * result.penetration;
		mCollisionPush.x = (std::abs(tempPush.x) > std::abs(mCollisionPush.x) ? tempPush.x : mCollisionPush.x);
		mCollisionPush.y = (std::abs(tempPush.y) > std::abs(mCollisionPush.y) ? tempPush.y : mCollisionPush.y);
		mCollisionPush.z = (std::abs(tempPush.z) > std::abs(mCollisionPush.z) ? tempPush.z : mCollisionPush.z);

		mLastCollideNormal = result.normal;

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
		mTransform->localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}

void Player::MoveHorizontal(float deltaTime)
{
	if (mIgnoreMoveInputTimer > 0.0f) return;

	float targetSpeed = mParam.walkSpeed;
	float accel = mParam.walkAccel;

	if (mTornado->IsSpinning())
	{
		targetSpeed = mParam.spinMoveSpeed;
		accel = mParam.spinMoveAccel;
	}
	else
	if (InputManager::GetInstance().IsDown(Input::Action::Dash))
	{
		targetSpeed = mParam.dashSpeed;
		accel = mParam.dashAccel;
	}

	Vector3 moveVec = InputManager::GetInstance().GetAsVector3(Input::Action::Move);

	// カメラを正面に移動
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	moveVec = right * moveVec.x + forward * moveVec.z;

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;

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

	float accelCoef = mOnGround ? 1.0f : mParam.airResistanceCoef;

	// XとZ成分だけ補間させる
	Vector3 vel = Vector3(mVelocity.x, 0.0f, mVelocity.z);
	vel = vel.Approach(moveVec * targetSpeed, accel * accelCoef);

	mVelocity.x = vel.x;
	mVelocity.z = vel.z;
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
