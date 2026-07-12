#include "Player.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "PlayerTornado.h"
#include "../Components/Collider3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "../Objects/DebugGround.h"
#include "Collision/Collision3D.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"
#include "Utility/Math.h"

namespace
{
	constexpr float kWalkSpeed = 200.0f;
	constexpr float kWalkAccel = 75.0f;

	constexpr float kDashCoef = 2.5f;

	constexpr float kAirCoef = 0.5f;

	constexpr float kJumpForce = 500.0f;
	constexpr float kJumpCancelThreshold = 50.0f;
	constexpr float kJumpBufferTime = 0.15f;

	constexpr float kWallJumpVerticalForce = 400.0f;
	constexpr float kWallJumpHorizontalForce = 500.0f;
	constexpr float kWallJumpIgnoreMoveInputTime = 0.2f;

	constexpr float kStickWallFallSpeed = 50.0f;
	constexpr float kStickWallCancelTimeThreshold = 0.5f;
	constexpr float kStickWallCancelMoveVectorThreshold = 0.5f;

	constexpr float kGravity = 980.0f;

	constexpr Vector3 kBodyCollisionSize{ 60.0f, 100.0f, 60.0f };
	constexpr Vector3 kBodyCollisionOffsetPos{ 0.0f, kBodyCollisionSize.y / 2.0f, 0.0f };

	constexpr Vector3 kFootCollisionSize{ kBodyCollisionSize.x, 1.0f, kBodyCollisionSize.z };
	constexpr Vector3 kFootCollisionOffsetPos{ 0.0f, -5.0f, 0.0f };

	const char* const kModelHandlePath = "";
}

Player::Player(PlayerBulletManager* bulletManager) :
	mLastMoveVec(Vector3::XAxis),
	mCanJumpTimer(0.0f),
	mIsJumping(false),
	mOnGround(false),
	mOnWall(false),
	mStickWallCancelTimer(0.0f),
	mIgnoreMoveInputTimer(0.0f),
	mModel(nullptr),
	mBodyCollider(nullptr),
	mFootCollider(nullptr),
	mTornado(nullptr)
{
	SetTag(Tag::Player);

	//mModel = std::make_unique<ModelRenderer>(this);

	mTornado = AddToChild<PlayerTornado>(bulletManager);

	mBodyCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, kBodyCollisionSize),
		this,
		Collider3D::Tag::Body
	);
	mFootCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, kFootCollisionSize),
		this,
		Collider3D::Tag::Foot
	);

	AddToChild<DebugGround>();
}

Player::~Player()
{
	mBodyCollider = nullptr;
	mModel = nullptr;
}

void Player::Init()
{
	//mModel->Load(kModelHandlePath);
}

void Player::Finalize()
{
}

void Player::Update()
{
	float deltaTime = TimeManager::GetDeltaTime();

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
}

void Player::PhysicsUpdate()
{
	mTransform.localPosition += mVelocity * TimeManager::GetDeltaTime();

	mBodyCollider->GetShape()->SetPosition(mTransform.CalculateWorldPosition() + kBodyCollisionOffsetPos);
	mFootCollider->GetShape()->SetPosition(mTransform.CalculateWorldPosition() + kFootCollisionOffsetPos);

	if (mOnGround) mOnWall = false;

	mOnGround = false;
}

void Player::Draw()
{
	Vector3 worldPos = mTransform.CalculateWorldPosition();

	//mModel->Draw();

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

	mBodyCollider->GetShape()->DebugDraw();
	mFootCollider->GetShape()->DebugDraw();
}

void Player::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (myCollider->GetTag() == Collider3D::Tag::Foot)
	{
		if (oppCollider->GetOwner()->GetTag() != Tag::Terrain) return;

		if (result.normal.y <= 0.5f) return;
		
		// 地面との衝突
		mCanJumpTimer = kJumpBufferTime;
		mOnGround = true;
		mIsJumping = false;

		return;
	}

	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:
		mCollisionPush += result.normal * result.penetration;

		mLastCollideNormal = result.normal;

		// TODO: 壁ジャンプと同時に壁と反対に入力すると壁に向かって壁ジャンプするバグ修正
		// 壁との衝突
		if ((std::abs(result.normal.x) > 0.5f || std::abs(result.normal.z) > 0.5f) && !Math::IsNearZero(result.penetration))
		{
			mOnWall = true;
		}

		// TODO: 壁がない場所に移動しても壁ずりがキャンセルされないバグ修正
		
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
		moveCoef *= kDashCoef;
	}

	// カメラを正面に移動
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	moveVec = right * moveVec.x + forward * moveVec.z;

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;

	float accelCoef = mOnGround ? 1.0f : kAirCoef;

	if (mOnWall)
	{
		Vector3 vec = mLastCollideNormal;
		std::swap(vec.x, vec.z);

		// 壁と逆方向に入力していたらタイマーをカウントアップ
		vec.z = -vec.z;
		Vector3 inputVec = moveVec.Cross(vec);
		if (inputVec.y > kStickWallCancelMoveVectorThreshold)
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
		if (mStickWallCancelTimer > kStickWallCancelTimeThreshold)
		{
			mStickWallCancelTimer = 0.0f;
			mOnWall = false;
		}
		
		// 壁ずり状態なら壁に沿って移動させる
		moveVec = vec * moveVec.Dot(vec);
	}

	mVelocity.x = Math::Approach(mVelocity.x, kWalkSpeed * moveCoef * moveVec.x, kWalkAccel * accelCoef);
	mVelocity.z = Math::Approach(mVelocity.z, kWalkSpeed * moveCoef * moveVec.z, kWalkAccel * accelCoef);
}

void Player::MoveVertical(float deltaTime)
{
	// ジャンプ
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && CanJump())
	{
		mVelocity.y = kJumpForce;
		mIsJumping = true;
		mCanJumpTimer = 0.0f;

		// 壁ジャンプ
		if (mOnWall && !mOnGround)
		{
			mVelocity.x = -mLastMoveVec.x * kWallJumpHorizontalForce;
			mVelocity.y = kWallJumpVerticalForce;
			mVelocity.z = -mLastMoveVec.z * kWallJumpHorizontalForce;

			mIgnoreMoveInputTimer = kWallJumpIgnoreMoveInputTime;

			mOnWall = false;
		}
	}
	// ジャンプキャンセル
	if (InputManager::GetInstance().IsReleased(Input::Action::Jump) && CanCancelJump())
	{
		mVelocity.y = kJumpCancelThreshold;
		mIsJumping = false;
	}

	// 落下処理
	if (!mOnGround)
	{
		if (mOnWall)
		{
			mVelocity.y = Math::Max(mVelocity.y - kGravity * deltaTime, -kStickWallFallSpeed);
		}
		else
		{
			mVelocity.y -= kGravity * deltaTime;
		}
	}
}

bool Player::CanJump()
{
	return mOnGround || mCanJumpTimer > 0.0f || mOnWall;
}

bool Player::CanCancelJump()
{
	return mIsJumping && mVelocity.y > kJumpCancelThreshold;
}
