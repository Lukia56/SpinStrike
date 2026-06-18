#pragma once

#include "ICamera.h"

/// <summary>
/// 静的なカメラ
/// カメラに何も設定しない場合に使用
/// </summary>
class CameraStatic : public ICamera
{
public:

	CameraStatic() = default;
	~CameraStatic() = default;

	void Update(Camera::View& view) override;
};

