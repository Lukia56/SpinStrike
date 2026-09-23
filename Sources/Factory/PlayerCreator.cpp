#include "PlayerCreator.h"
#include <string>
#include <vector>
#include "Param/Param.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Character/Player.h"
#include "World/Character/PlayerTornado.h"

PlayerCreator::PlayerCreator(const std::string& modelPath, const std::string& playerParamPath, const std::string& aabbParamPath, const std::string& initData, PlayerTornado* tornado) :
	mModelPath(modelPath),
	mPlayerParamPath(playerParamPath),
	mAABBParamPath(aabbParamPath),
	mInitDataPath(initData),
	mTornado(tornado)
{
}

std::unique_ptr<Player> PlayerCreator::CreateInstance()
{
	std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(mModelPath);
	PlayerParam param = Data::Csv::LoadCsvAs<PlayerParam>(mPlayerParamPath)[0];
	std::vector<AABBColliderParam> aabbParam = Data::Csv::LoadCsvAs<AABBColliderParam>(mAABBParamPath);
	PlayerInitData initData = Data::Json::LoadJsonAs<PlayerInitData>(mInitDataPath)[0];

	auto instance = std::make_unique<Player>(model, param, aabbParam, initData, mTornado);

	return instance;
}
