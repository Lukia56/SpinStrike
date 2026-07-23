#include "SceneTest.h"
#include <DxLib.h>
#include "World/Characters/Player.h"
#include "World/Characters/PlayerBulletManager.h"
#include "World/Objects/Crate.h"
#include "World/Objects/TestBox.h"
#include "World/Others/RootObject.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "System/Input/Mouse.h"
#include "Utility/Data/CSV/CsvLoader.h"

SceneTest::SceneTest() :
	mPointLight(-1),
	mPlayer(nullptr)
{
	auto bulletManager = AddToRoot<PlayerBulletManager>();

	mPlayer = AddToRoot<Player>(bulletManager);

	auto objectRoot = AddToRoot<RootObject>();

	auto crate = objectRoot->AddToChild<Crate>();
	crate->GetTransform().localPosition = Vector3(500.0f, 0.0f, 0.0f);

	auto terrainRoot = AddToRoot<RootObject>();

	auto floorBox = terrainRoot->AddToChild<TestBox>(Vector3(10000.0f, 100.0f, 10000.0f));
	floorBox->GetTransform().localPosition = Vector3(0.0f, -50.0f, 0.0f);
	auto wallBoxA = terrainRoot->AddToChild<TestBox>(Vector3(100.0f, 1000.0f, 1000.0f));
	wallBoxA->GetTransform().localPosition = Vector3(150.0f, 500.0f, 0.0f);
	auto wallBoxB = terrainRoot->AddToChild<TestBox>(Vector3(100.0f, 1000.0f, 1000.0f));
	wallBoxB->GetTransform().localPosition = Vector3(-150.0f, 500.0f, 0.0f);

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
