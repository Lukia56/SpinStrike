#include "Player.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "PlayerTornado.h"
#include "../Components/Collision3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "../Objects/DebugGround.h"
#include "System/CollisionManager.h"
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

	constexpr float kGravity = 980.0f;

	constexpr Vector3 kCollisionSize{ 60.0f, 100.0f, 60.0f };

	constexpr Vector3 kCollisionOffsetPos{ 0.0f, kCollisionSize.y / 2.0f, 0.0f };

	const char* const kModelHandlePath = "";
}

Player::Player(PlayerBulletManager* bulletManager) :
	mLastMoveVec(Vector3::XAxis),
	mCanJumpTimer(0.0f),
	mIsJumping(false),
	mOnGround(false),
	mModel(nullptr),
	mCollider(nullptr),
	mTornade(nullptr)
{
	mTornade = AddToChild<PlayerTornado>(bulletManager);

	//mModel = std::make_unique<ModelRenderer>(this);
	mCollider = std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize);
	CollisionManager::GetInstance().Register(this, mCollider.get(), Collision::Tag::Player);

	AddToChild<DebugGround>();
}

Player::~Player()
{
	CollisionManager::GetInstance().Unregister(mCollider.get());
	mCollider = nullptr;
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

	MoveHorizontal(deltaTime);
	MoveVertical(deltaTime);

	if (InputManager::GetInstance().IsPressed(Input::Action::Spin))
	{
		mTornade->SetSpinningFlag(true);
	}
	if (InputManager::GetInstance().IsReleased(Input::Action::Spin))
	{
		mTornade->CreateBullet(mLastMoveVec);

		mTornade->SetSpinningFlag(false);
	}

	mTransform.localPosition += mVelocity * deltaTime;

	if (mCanJumpTimer > 0.0f) mCanJumpTimer -= TimeManager::GetDeltaTime();

	// 地面がないため仮
	if (mTransform.CalculateWorldPosition().y < 0.0f)
	{
		mTransform.localPosition.y -= mTransform.CalculateWorldPosition().y;
		mVelocity.y = 0.0f;
		mCanJumpTimer = kJumpBufferTime;

		mOnGround = true;
		mIsJumping = false;
	}
	else
	{
		mOnGround = false;
	}

	mCollider->SetPosition(mTransform.CalculateWorldPosition() + kCollisionOffsetPos);
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

		ImGui::Text("CanJumpTimer: %f", mCanJumpTimer);

		ImGui::Text("IsJumping: %d", mIsJumping);
		ImGui::Text("OnGround: %d", mOnGround);

		ImGui::End();
	}

	mCollider->DebugDraw();
}

void Player::OnCollision(GameObject* other, const Collision::Result& result, Collision::Tag tag)
{
	switch (tag)
	{
	case Collision::Tag::Terrain:
		mTransform.localPosition += result.normal * result.penetration;

		// 地面との衝突
		if (result.normal.y > 0.5f)
		{
			mVelocity.y = Math::Max(mVelocity.y, 0.0f);
			mCanJumpTimer = kJumpBufferTime;
			mOnGround = true;
			mIsJumping = false;
		}
		// 天井との衝突
		if (result.normal.y < -0.5f)
		{
			mVelocity.y = Math::Min(mVelocity.y, 0.0f);
		}
		break;
	}
}

void Player::MoveHorizontal(float deltaTime)
{
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

	float accelCoef = mOnGround ? 1.0f : kAirCoef;

	mVelocity.x = Math::Approach(mVelocity.x, kWalkSpeed * moveCoef * moveVec.x, kWalkAccel * accelCoef);
	mVelocity.z = Math::Approach(mVelocity.z, kWalkSpeed * moveCoef * moveVec.z, kWalkAccel * accelCoef);

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;
}

void Player::MoveVertical(float deltaTime)
{
	// ジャンプ
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && CanJump())
	{
		mVelocity.y = kJumpForce;
		mIsJumping = true;
		mCanJumpTimer = 0.0f;
	}
	// ジャンプキャンセル
	if (InputManager::GetInstance().IsReleased(Input::Action::Jump) && CanCancelJump())
	{
		mVelocity.y = kJumpCancelThreshold;
		mIsJumping = false;
	}

	mVelocity.y -= kGravity * deltaTime;
}

bool Player::CanJump()
{
	return mOnGround || mCanJumpTimer > 0.0f;
}

bool Player::CanCancelJump()
{
	return mIsJumping && mVelocity.y > kJumpCancelThreshold;
}
