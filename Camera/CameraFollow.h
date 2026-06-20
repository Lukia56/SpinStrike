#pragma once

#include "ICamera.h"

class Transform;

/// <summary>
/// ターゲットを追従し、視点操作が出来るカメラ
/// </summary>
class CameraFollow : public ICamera
{
public:

	CameraFollow(Transform* target);
	~CameraFollow() = default;

	void Update(Camera::View& view) override;

private:

	Vector3 mEyePosition;

	Vector3 mRotation;

	Transform* mTarget;
};
