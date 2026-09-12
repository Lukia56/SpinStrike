#include "SceneStageTest.h"
#include <vector>
#include "SceneSelectDebug.h"
#include "World/Character/Player.h"
#include "World/Character/PlayerBulletManager.h"
#include "World/Character/Enemy.h"
#include "World/Other/RootObject.h"
#include "World/Other/StageManager.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "Utility/Data/JSON/JsonLoader.h"

namespace
{
	const char* const kStageObjectDataPath = "Resources\\MasterData\\TestStage0.json";

	const char* const kWaypointDataPath = "Resources\\MasterData\\TestStageWaypoint0.json";

	const char* const kPatrollingDataPath = "Resources\\MasterData\\TestEnemyMoveData.json";
}

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr),
	mEnemy(nullptr)
{
}

SceneStageTest::~SceneStageTest()
{
}

void SceneStageTest::OnInit()
{
	auto objectRoot = CreateToRoot<RootObject>();

	PlayerBulletManager* bulletManager = objectRoot->CreateToChild<PlayerBulletManager>();

	mPlayer = objectRoot->CreateToChild<Player>(bulletManager);
	mPlayer->GetTransform()->localPosition.y = 200.0f;


	std::vector<WaypointGroup> waypointGroups = Data::Json::LoadJsonAs<WaypointGroup>(kWaypointDataPath);

	std::vector<EnemyPatrollingData> patrollingData = std::move(Data::Json::LoadJsonAs<EnemyPatrollingData>(kPatrollingDataPath));

	mEnemy = objectRoot->CreateToChild<Enemy>(mPlayer->GetTransform(), std::move(patrollingData[0]), waypointGroups);
	mEnemy->GetTransform()->localPosition = Vector3(0.0f, 100.0f, 0.0f);


	objectRoot->CreateToChild<StageManager>(kStageObjectDataPath);

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

void SceneStageTest::OnFinalize()
{
}

std::unique_ptr<SceneBase> SceneStageTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_LALT))
	{
		Mouse::GetInstance().SetMode(Mouse::Mode::Absolute);
	}
	else
	{
		Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
	}

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
