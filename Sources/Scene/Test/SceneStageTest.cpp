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
#include "World/Character/Enemy.h"
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

	const char* const kPatrollingDataPath = "Resources\\MasterData\\Enemy\\TestEnemy\\WaypointActionData.json";

	const char* const kSkullEnemyModelPath = "Resources\\Model\\Skull.mv1";
	const char* const kSkullEnemyAnimParamPath = "Resources\\MasterData\\Enemy\\Skull\\AnimationParam.csv";

	constexpr Vector3 kGoalPos{ 0.0f, 250.0f, 500.0f };
}

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr),
	mEnemy(nullptr),
	mGameOverObserver(nullptr),
	mGoalObserver(nullptr)
{
}

SceneStageTest::~SceneStageTest()
{
}

void SceneStageTest::OnInit()
{
	auto objectRoot = CreateToRoot<RootObject>();

	// ƒvƒŒƒCƒ„[‚ð¶¬‚·‚é
	PlayerBulletManager* bulletManager = objectRoot->CreateToChild<PlayerBulletManager>();
	std::unique_ptr<PlayerTornado> tornado = std::make_unique<PlayerTornado>(bulletManager);

	std::unique_ptr<PlayerCreator> playerCreator = std::make_unique<PlayerCreator>(kPlayerInitDataPath, std::move(tornado));
	mPlayer = objectRoot->AddToChild(std::move(playerCreator->CreateInstance()));


	{
		std::vector<WaypointGroup> waypointGroups = Data::Json::LoadJsonAs<WaypointGroup>(kWaypointDataPath);

		std::vector<EnemyPatrollingData> patrollingData = std::move(Data::Json::LoadJsonAs<EnemyPatrollingData>(kPatrollingDataPath));

		std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkullEnemyModelPath);
		std::vector<AnimationParam> animParam = Data::Csv::LoadCsvAs<AnimationParam>(kSkullEnemyAnimParamPath);

		mEnemy = objectRoot->CreateToChild<Enemy>(mPlayer->GetTransform(), std::move(patrollingData[0]), waypointGroups, model, animParam);
		mEnemy->GetTransform()->localPosition = Vector3(0.0f, 100.0f, 0.0f);
	}


	objectRoot->CreateToChild<StageManager>(kStageObjectDataPath);
	GoalObject* goal = objectRoot->CreateToChild<GoalObject>();
	goal->GetTransform()->localPosition = kGoalPos;

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
