#pragma once

#include "ICamera.h"

class Transform;

class CameraFollow : public ICamera
{
public:

	CameraFollow(Transform* target);
	~CameraFollow() = default;

	void Update(Camera::View& view) override;

private:

	Vector3 mPosition;

	Transform* mTarget;
};
