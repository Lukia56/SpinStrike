#include "SceneTest.h"
#include <DxLib.h>
#include "../World/Characters/Player.h"
#include "../World/Objects/Crate.h"
#include "../World/Objects/TestBox.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "System/Input/Mouse.h"

SceneTest::SceneTest() :
	mPointLight(-1),
	mPlayer(nullptr),
	mCrate(nullptr)
{
	mPlayer = AddToRoot<Player>();
	mCrate = AddToRoot<Crate>();
	mCrate->GetTransform().localPosition = Vector3(500.0f, 0.0f, 0.0f);

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
	mPointLight = CreatePointLightHandle(VGet(0.0f, 100.0f, 0.0f), 2000.0f, 0.0f, 0.001f, 0.0f);
	SetLightDifColorHandle(mPointLight, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	SetLightSpcColorHandle(mPointLight, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

void SceneTest::Finalize()
{
	DeleteLightHandle(mPointLight);
}

std::unique_ptr<SceneBase> SceneTest::Update()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	return nullptr;
}
