#include "SceneStageTest.h"
#include <vector>
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Factory/PlayerCreator.h"
#include "Observer/GameOverObserver.h"
#include "Observer/GoalObserver.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Character/Player.h"
#include "World/Character/PlayerBulletManager.h"
#include "World/Character/PlayerTornado.h"
#include "World/Character/EnemyManager.h"
#include "World/Object/GoalObject.h"
#include "World/Other/RootObject.h"
#include "World/Other/StageManager.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/InGameScreen.h"

namespace
{
	const char* const kStageObjectDataPath = "Resources\\MasterData\\Stage\\TestStage\\StageData.json";
	const char* const kWaypointDataPath = "Resources\\MasterData\\Stage\\TestStage\\WaypointData.json";
	const char* const kPlayerInitDataPath = "Resources\\MasterData\\Stage\\TestStage\\PlayerInitData.json";
	const char* const kEnemyInitDataPath = "Resources\\MasterData\\Stage\\TestStage\\EnemyInitData.json";

	const char* const kPatrollingDataPath = "Resources\\MasterData\\Enemy\\TestEnemy\\WaypointActionData.json";

	const char* const kSkullEnemyModelPath = "Resources\\Model\\Skull.mv1";
	const char* const kSkullEnemyAnimParamPath = "Resources\\MasterData\\Enemy\\Skull\\AnimationParam.csv";

	const char* const kGoalModelPath = "Resources\\Model\\flag_B_red.mv1";

	constexpr Vector3 kGoalPos{ 0.0f, 250.0f, 500.0f };

	constexpr int kBulletMaxNum = 10;
}

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr),
	mGameOverObserver(nullptr),
	mGoalObserver(nullptr)
{
}

SceneStageTest::~SceneStageTest()
{
}

void SceneStageTest::OnInit()
{
	CreateToRoot<StageManager>(kStageObjectDataPath);
	{
		std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(kGoalModelPath);
		GoalObject* goal = CreateToRoot<GoalObject>(model);
		goal->GetTransform()->localPosition = kGoalPos;
	}

	// プレイヤーを生成する
	{
		// 丸影の透明度が自分より前に生成したオブジェクトに対してのみ適用されるため、ステージより後に生成する
		PlayerBulletManager* bulletManager = CreateToRoot<PlayerBulletManager>(kBulletMaxNum);
		std::unique_ptr<PlayerTornado> tornado = std::make_unique<PlayerTornado>(bulletManager);

		std::unique_ptr<PlayerCreator> playerCreator = std::make_unique<PlayerCreator>(kPlayerInitDataPath, std::move(tornado));
		mPlayer = AddToRoot(std::move(playerCreator->CreateInstance()));
	}

	// 敵を生成する
	{
		std::vector<EnemyInitData> enemyInitData = Data::Json::LoadJsonAs<EnemyInitData>(kEnemyInitDataPath);
		std::vector<WaypointGroup> waypointGroups = Data::Json::LoadJsonAs<WaypointGroup>(kWaypointDataPath);

		CreateToRoot<EnemyManager>(enemyInitData, waypointGroups, mPlayer->GetTransform());
	}

	UI::UIManager* uiManager = CreateToRoot<UI::UIManager>();
	uiManager->AddScreenToPool(std::make_unique<UI::InGameScreen>(mPlayer));
	uiManager->PushScreen<UI::InGameScreen>();

	mGameOverObserver = std::make_unique<Observer::GameOverObserver>(mPlayer);
	mGoalObserver = std::make_unique<Observer::GoalObserver>(mPlayer);

	mPlayer->GetEventSubject()->RegisterObserver(mGameOverObserver.get());
	mPlayer->GetEventSubject()->RegisterObserver(mGoalObserver.get());

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
