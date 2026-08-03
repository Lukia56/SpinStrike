#include "PlayerBullet.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kMoveSpeed = 800.0f;
}

PlayerBullet::PlayerBullet(const Vector3& moveVec) :
	mMoveVec(moveVec)
{
}

void PlayerBullet::Init()
{
}

void PlayerBullet::Update()
{
	mTransform.localPosition += mMoveVec * kMoveSpeed * TimeManager::GetDeltaTime();
}

void PlayerBullet::DebugDraw()
{
	DrawSphere3D(mTransform.CalculateWorldPosition().GetAsDxLibVector(), 20.0f, 8, Color::red.GetAsHexRGB(), Color::red.GetAsHexRGB(), false);
}
