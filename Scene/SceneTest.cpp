#include "SceneTest.h"
#include <DxLib.h>
#include "../World/Characters/Player.h"
#include "../World/Objects/TestBox.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "System/Input/Mouse.h"

SceneTest::SceneTest() :
	mPlayer(nullptr)
{
	mPlayer = AddToRoot<Player>();

	auto floorBox = AddToRoot<TestBox>();
	auto ceilingBox = AddToRoot<TestBox>();
	ceilingBox->GetTransform().Translate(Vector3(0.0f, 350.0f, 0.0f));

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

	//Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

void SceneTest::Finalize()
{
}

std::unique_ptr<SceneBase> SceneTest::Update()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	return nullptr;
}
