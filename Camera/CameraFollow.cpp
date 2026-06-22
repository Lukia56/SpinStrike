#include "CameraFollow.h"
#include "System/InputManager.h"
#include "System/Input/Mouse.h"
#include "Utility/Math.h"
#include "World/Components/Transform.h"

namespace
{
	constexpr float kDistance = 400.0f;

	constexpr float kMaxPitch = 80.0f;
	constexpr float kMinPitch = -80.0f;
}

CameraFollow::CameraFollow(Transform* target) :
	mEyePosition(Vector3::Zero),
	mRotation(Vector3::Zero),
	mTarget(target)
{
}

void CameraFollow::Update(Camera::View& view)
{
	// 視点を移動する
	Vector2 relative = Mouse::GetInstance().GetRelative();
	mRotation += Vector3(relative.y, relative.x, 0.0f) * Math::ToRadian(1.0f);

	// ピッチを制限する
	mRotation.x = Math::Clamp(mRotation.x, Math::ToRadian(kMinPitch), Math::ToRadian(kMaxPitch));

	Vector3 targetPos = mTarget->CalculateWorldPosition();

	float yawSinParam = std::sin(mRotation.y);
	float yawCosParam = std::cos(mRotation.y);
	float pitchSinParam = std::sin(mRotation.x);
	float pitchCosParam = std::cos(mRotation.x);

	// 回転させたカメラの座標を計算
	Vector3 rotatedOffsetPos;
	rotatedOffsetPos.x = pitchCosParam * yawSinParam * kDistance;
	rotatedOffsetPos.y = pitchSinParam * kDistance;
	rotatedOffsetPos.z = pitchCosParam * yawCosParam * kDistance;

	mEyePosition = targetPos + rotatedOffsetPos;

	view.eyePosition = mEyePosition;
	view.targetPosition = targetPos;
}
