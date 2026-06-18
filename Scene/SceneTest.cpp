#include "SceneTest.h"
#include <DxLib.h>
#include "../World/Characters/Player.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"

SceneTest::SceneTest() :
	mPlayer(nullptr)
{
	mPlayer = AddToRoot(std::make_unique<Player>());

	//GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	//GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
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
