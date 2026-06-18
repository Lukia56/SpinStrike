#pragma once

#include "ICamera.h"
#include "Utility/Vector.h"

/// <summary>
/// フリーに移動できるデバッグ用カメラ
/// </summary>
class CameraDebugFree : public ICamera
{
public:

	CameraDebugFree() = default;
	~CameraDebugFree() = default;

	void Update(Camera::View& view) override;

	void DebugDraw() override;

private:

	void Look();

	void Move();

	void DrawCrossHair();

private:

	Vector3 mPosition;
	Vector3 mRotation;
};
