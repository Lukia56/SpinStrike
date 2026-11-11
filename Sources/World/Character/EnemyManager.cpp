#include "EnemyManager.h"
#include "Enemy.h"
#include "Param/Param.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Data/JSON/JsonLoader.h"

namespace
{
	const char* const kPatrollingDataPath[] = {
		"Resources\\MasterData\\Stage\\TestStage\\EnemyWaypointAction\\0.json",
		"Resources\\MasterData\\Stage\\TestStage\\EnemyWaypointAction\\1.json",
	};

	const char* const kSkullEnemyModelPath = "Resources\\Model\\Skull.mv1";
	const char* const kSkullEnemyAnimParamPath = "Resources\\MasterData\\Enemy\\Skull\\AnimationParam.csv";
}

EnemyManager::EnemyManager(const std::vector<EnemyInitData>& enemyInitData, const std::vector<WaypointGroup>& waypointGroups, Transform* playerTransform)
{
	std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkullEnemyModelPath);
	std::vector<AnimationParam> animParam = Data::Csv::LoadCsvAs<AnimationParam>(kSkullEnemyAnimParamPath);

	for (auto& data : enemyInitData)
	{
		EnemyPatrollingData patrollingData = std::move(Data::Json::LoadJsonAs<EnemyPatrollingData>(kPatrollingDataPath[data.patrolDataID])[0]);

		GameObject* enemy = CreateToChild<Enemy>(playerTransform, std::move(patrollingData), waypointGroups, model, animParam);
		enemy->GetTransform()->localPosition = data.transform.position;
	}
}

void EnemyManager::Init()
{
}

void EnemyManager::Update()
{
}
