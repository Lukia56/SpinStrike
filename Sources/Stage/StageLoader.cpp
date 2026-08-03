#include "StageLoader.h"
#include <vector>
#include "Stage/StageModelDataBase.h"
#include "Factory/StageObjectCreator.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/GameObject.h"

namespace Stage
{
	std::vector<std::unique_ptr<GameObject>> StageLoader::Load(const std::string& path)
	{
		std::vector<StageObjectParam> params = Data::Json::LoadJsonAs<StageObjectParam>(path);

		if (params.empty()) return {};

		std::vector<std::unique_ptr<GameObject>> loadedObjects;

		auto dataBase = std::make_unique<Stage::StageModelDataBase>();

		auto stageObjectCreator = std::make_unique<StageObjectCreator>(dataBase.get());

		// ステージオブジェクト生成
		for (const auto& param : params)
		{
			stageObjectCreator->SetParam(param);
			loadedObjects.emplace_back(stageObjectCreator->CreateInstance());
		}

		return loadedObjects;
	}
}
