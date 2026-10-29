#include "CameraFollow.h"
#include <imgui.h>
#include "Collision/CollisionManager.h"
#include "System/InputManager.h"
#include "System/Input/Mouse.h"
#include "Utility/Math.h"
#include "World/GameObject.h"
#include "World/Component/Transform.h"
#include "World/Component/Collider3D.h"

namespace
{
	constexpr Vector3 kOffsetPos{ 0.0f, 100.0f, 0.0f };

	constexpr float kDistance = 400.0f;

	constexpr float kMaxPitch = 80.0f;
	constexpr float kMinPitch = -80.0f;

	constexpr float kRaycastCollidePointDistance = -16.0f;

	constexpr float kMoveEyeLatency = 0.5f;
	constexpr float kMoveViewLatency = 0.25f;

	constexpr float kSensitivity = 0.25f;
}

CameraFollow::CameraFollow(Transform* target) :
	mEyePosition(Vector3::Zero),
	mRotation(Vector3::Zero),
	mTargetRotation(Vector3::Zero),
	mTarget(target)
{
}

void CameraFollow::Update(Camera::View& view)
{
	// 視点を移動する
	Vector2 relative = Mouse::GetInstance().GetRelativePos() * kSensitivity;
	mTargetRotation += Vector3(relative.y, relative.x, 0.0f) * Math::ToRadian(1.0f);

	// ピッチを制限する
	mTargetRotation.x = Math::Clamp(mTargetRotation.x, Math::ToRadian(kMinPitch), Math::ToRadian(kMaxPitch));

	mRotation = mRotation.Lerp(mTargetRotation, kMoveViewLatency);

	Vector3 targetPos = mTarget->CalculateWorldPosition() + kOffsetPos;

	float yawSinParam = std::sin(mRotation.y);
	float yawCosParam = std::cos(mRotation.y);
	float pitchSinParam = std::sin(mRotation.x);
	float pitchCosParam = std::cos(mRotation.x);

	// 回転させたカメラの座標を計算
	Vector3 rotatedOffsetPos;
	rotatedOffsetPos.x = pitchCosParam * yawSinParam;
	rotatedOffsetPos.y = pitchSinParam;
	rotatedOffsetPos.z = pitchCosParam * yawCosParam;

	mEyePosition = targetPos + rotatedOffsetPos * kDistance;

	// 地形をすり抜けないようにする
	Collision::Ray ray = Collision::Ray{ .position = targetPos, .direction = rotatedOffsetPos.GetNormalize(), .maxDistance = kDistance};
	auto result = CollisionManager::GetInstance().Raycast(ray,
		[](Collider3D* collider)
		{
			return collider->GetOwner()->GetTag() == GameObject::Tag::Terrain;
		});

	if (!result.empty())
	{
		mEyePosition = targetPos + rotatedOffsetPos * (result[0].distance + kRaycastCollidePointDistance);
	}

	view.eyePosition = view.eyePosition.Lerp(mEyePosition, kMoveEyeLatency);
	view.targetPosition = targetPos;
}

void CameraFollow::DebugDraw()
{
	if (ImGui::Begin("Camera"))
	{
		float eyePosPtr[] = { mEyePosition.x, mEyePosition.y, mEyePosition.z };
		ImGui::InputFloat3("EyePosition", eyePosPtr, "%.1f");

		Vector3 targetPos = mTarget->CalculateWorldPosition();
		float targetPosPtr[] = { targetPos.x, targetPos.y, targetPos.z };
		ImGui::InputFloat3("TargetPosition", targetPosPtr, "%.1f");

		float rotPtr[] = { Math::ToDegree(mRotation.x), Math::ToDegree(mRotation.y), Math::ToDegree(mRotation.z) };
		ImGui::InputFloat3("Rotation", rotPtr, "%.1f");

		ImGui::End();
	}
}
