#include "PlayerBullet.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kMoveSpeed = 800.0f;

	constexpr float kLifeTime = 3.0f;
}

PlayerBullet::PlayerBullet()
{
}

void PlayerBullet::Init()
{
}

void PlayerBullet::Update()
{
	if (mDestroyTimer > 0.0f)
	{
		mDestroyTimer -= TimeManager::GetDeltaTime();
	}
}

void PlayerBullet::PhysicsUpdate()
{
	mTransform->localPosition += mMoveVec * kMoveSpeed * TimeManager::GetDeltaTime();
}

void PlayerBullet::DebugDraw()
{
	DrawSphere3D(mTransform->CalculateWorldPosition().GetAsDxLibVector(), 20.0f, 8, Color::red.GetAsHexRGB(), Color::red.GetAsHexRGB(), false);
}

void PlayerBullet::Setup(const Vector3& pos, const Vector3& moveVec)
{
	mTransform->localPosition = pos;

	mMoveVec = moveVec;

	mDestroyTimer = kLifeTime;
}
