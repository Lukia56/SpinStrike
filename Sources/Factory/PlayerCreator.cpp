#include "PlayerCreator.h"
#include <string>
#include <vector>
#include "Param/Param.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Resource/Texture.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Character/Player.h"
#include "World/Character/PlayerTornado.h"

namespace
{
	const char* const kModelPath = "Resources\\Model\\Hero.x";
	const char* const kParamPath = "Resources\\MasterData\\Player\\PlayerParam.csv";
	const char* const kAABBParamPath = "Resources\\MasterData\\Player\\PlayerAABBColliderParam.csv";

	const char* const kBlobShadowTexturePath = "Resources\\Sprite\\BlobShadow.png";
}

PlayerCreator::PlayerCreator(const std::string& initData, PlayerTornado* tornado) :
	mInitDataPath(initData),
	mTornado(tornado)
{
}

std::unique_ptr<Player> PlayerCreator::CreateInstance()
{
	std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath);
	PlayerParam param = Data::Csv::LoadCsvAs<PlayerParam>(kParamPath)[0];
	std::vector<AABBColliderParam> aabbParam = Data::Csv::LoadCsvAs<AABBColliderParam>(kAABBParamPath);

	PlayerInitData initData = Data::Json::LoadJsonAs<PlayerInitData>(mInitDataPath)[0];

	std::shared_ptr<Resource::ResourceBase> blobShadowTexture = ResourceManager::GetInstance().GetResource<Resource::Texture>(kBlobShadowTexturePath);

	auto instance = std::make_unique<Player>(model, blobShadowTexture, param, aabbParam, initData, mTornado);

	return instance;
}
