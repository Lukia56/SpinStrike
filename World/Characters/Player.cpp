#include "Player.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include "../Components/Collision3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

namespace
{
	constexpr float kWalkSpeed = 200.0f;
	constexpr float kWalkAccel = 75.0f;

	constexpr float kDashCoef = 2.5f;

	constexpr float kJumpForce = 500.0f;

	constexpr float kJumpCancelThreshold = 50.0f;

	constexpr float kGravity = 980.0f;

	constexpr Vector3 kCollisionSize{ 60.0f, 100.0f, 60.0f };

	constexpr Vector3 kCollisionOffsetPos{ 0.0f, kCollisionSize.y / 2.0f, 0.0f };

	const char* const kModelHandlePath = "";
}

Player::Player() :
	mIsJumping(false),
	mOnGround(false),
	mModel(nullptr),
	mCollider(nullptr)
{
	//mModel = std::make_unique<ModelRenderer>(this);
	mCollider = std::make_unique<Collision3D::AABB3D>(Vector3::Zero, kCollisionSize);
}

Player::~Player()
{
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

	mTransform.localPosition += mVelocity * deltaTime;

	// 地面がないため仮
	if (mTransform.CalculateWorldPosition().y < 0.0f)
	{
		mTransform.localPosition.y -= mTransform.CalculateWorldPosition().y;
		mVelocity.y = 0.0f;

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
	//mModel->Draw();

	printfDx("Velocity.x = %f\n", mVelocity.x);
	printfDx("Velocity.y = %f\n", mVelocity.y);
	printfDx("Velocity.z = %f\n", mVelocity.z);

	mCollider->DebugDraw();
}

void Player::MoveHorizontal(float deltaTime)
{
	// 水平方向の移動
	Vector3 moveVec = InputManager::GetInstance().GetAsVector3(Input::Action::Move);

	// ダッシュ
	if (InputManager::GetInstance().IsDown(Input::Action::Dash))
	{
		moveVec *= kDashCoef;
	}

	// カメラを正面に移動
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	Vector3 worldMoveVec = right * moveVec.x + forward * moveVec.z;

	mVelocity.x = Math::Approach(mVelocity.x, kWalkSpeed * worldMoveVec.x, kWalkAccel);
	mVelocity.z = Math::Approach(mVelocity.z, kWalkSpeed * worldMoveVec.z, kWalkAccel);
}

void Player::MoveVertical(float deltaTime)
{
	// ジャンプ
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && mOnGround)
	{
		mVelocity.y = kJumpForce;
		mIsJumping = true;
	}
	// ジャンプキャンセル
	if (InputManager::GetInstance().IsReleased(Input::Action::Jump) && mIsJumping && mVelocity.y > kJumpCancelThreshold)
	{
		mVelocity.y = kJumpCancelThreshold;
		mIsJumping = false;
	}

	mVelocity.y -= kGravity * deltaTime;
}
