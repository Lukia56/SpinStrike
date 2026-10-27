#include "PlayerCreator.h"
#include <string>
#include <vector>
#include "Param/Param.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Resource/Texture.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Character/Player.h"
#include "World/Character/PlayerTornado.h"

namespace
{
	const char* const kModelPath = "Resources\\Model\\Hero.x";

	const char* const kBlobShadowTexturePath = "Resources\\Sprite\\BlobShadow.png";
}

PlayerCreator::PlayerCreator(const std::string& initData, std::unique_ptr<PlayerTornado> tornado) :
	mInitDataPath(initData),
	mTornado(std::move(tornado))
{
}

std::unique_ptr<Player> PlayerCreator::CreateInstance()
{
	PlayerInitData initData = Data::Json::LoadJsonAs<PlayerInitData>(mInitDataPath)[0];

	std::shared_ptr<Resource::ResourceBase> model = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath);
	std::shared_ptr<Resource::ResourceBase> blobShadowTexture = ResourceManager::GetInstance().GetResource<Resource::Texture>(kBlobShadowTexturePath);

	auto instance = std::make_unique<Player>(model, blobShadowTexture, initData, std::move(mTornado));

	return instance;
}
