#include "CameraManager.h"
#include <cassert>
#include <DxLib.h>
#include "ICamera.h"
#include "Utility/Math.h"

namespace
{
	constexpr float kInitFOV = 70.0f;

	constexpr float kInitNearClip = 5.0f;
	constexpr float kInitFarClip = 5000.0f;
}

CameraManager::CameraManager() :
	mCurrentCameraType(Camera::Type::Static),
	mView{ .fov = Math::ToRadian(kInitFOV), .nearClip = kInitNearClip, .farClip = kInitFarClip }
{
	// .fillだとエラーになるためforループ
	for (auto& it : mCameras)
	{
		it = nullptr;
	}
}

CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	ICamera* camera = mCameras[static_cast<size_t>(mCurrentCameraType)].get();

	if (!camera)
	{
		assert(false && "CameraManager // 現在のカメラがnullptrです");
		return;
	}

	camera->Update(mView);
}

void CameraManager::DebugDraw() const
{
	mCameras[static_cast<size_t>(mCurrentCameraType)]->DebugDraw();
}

void CameraManager::Bind() const
{
	SetupCamera_Perspective(mView.fov);
	SetCameraNearFar(mView.nearClip, mView.farClip);

	SetCameraPositionAndTarget_UpVecY(mView.eyePosition.GetAsDxLibVector(), mView.targetPosition.GetAsDxLibVector());
}

void CameraManager::AddCamera(Camera::Type type, std::unique_ptr<ICamera> camera)
{
	mCameras[static_cast<size_t>(type)] = std::move(camera);
}
