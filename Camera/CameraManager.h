#pragma once

#include <array>
#include <memory>
#include "Camera/CameraProperty.h"

class ICamera;

/// <summary>
/// カメラとビュー射影を管理するクラス
/// </summary>
class CameraManager
{
public:

	CameraManager();
	~CameraManager();

	/// <summary>
	/// カメラを更新する
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグ情報とクロスヘアーを表示する
	/// </summary>
	void DebugDraw() const;

	/// <summary>
	/// ビュー射影を適用させる
	/// </summary>
	void Bind() const;

	void AddCamera(Camera::Type type, std::unique_ptr<ICamera> camera);

	void SetCurrentCameraType(Camera::Type type) { mCurrentCameraType = type; }

private:

	Camera::Type mCurrentCameraType;

	Camera::View mView;

	std::array<std::unique_ptr<ICamera>, static_cast<size_t>(Camera::Type::Max)> mCameras;
};
