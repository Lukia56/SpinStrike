#pragma once

#include "ICamera.h"

class Transform;

class CameraFollow : public ICamera
{
public:

	CameraFollow() = default;
	~CameraFollow() = default;

	void Update(Camera::View& view) override;

private:

	Transform* mTarget;

	Vector3 mPosition;
};
