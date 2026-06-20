#include "SceneTest.h"
#include <DxLib.h>
#include "../World/Characters/Player.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"

SceneTest::SceneTest() :
	mPlayer(nullptr)
{
	mPlayer = AddToRoot<Player>();

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(&mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);
}

SceneTest::~SceneTest()
{
	mPlayer = nullptr;
}

void SceneTest::Init()
{
	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
}

void SceneTest::Finalize()
{
}

std::unique_ptr<SceneBase> SceneTest::Update()
{
	return nullptr;
}
