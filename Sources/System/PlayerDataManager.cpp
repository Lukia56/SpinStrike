#include "PlayerDataManager.h"
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kParamPath = "Resources\\MasterData\\Player\\PlayerParam.csv";
	const char* const kAABBParamPath = "Resources\\MasterData\\Player\\PlayerAABBColliderParam.csv";
}

void PlayerDataManager::Initialize()
{
	mPlayerParam = Data::Csv::LoadCsvAs<PlayerParam>(kParamPath)[0];

	mAABBParams = Data::Csv::LoadCsvAs<AABBColliderParam>(kAABBParamPath);
}

PlayerDataManager& PlayerDataManager::GetInstance()
{
	static PlayerDataManager instance;

	return instance;
}
