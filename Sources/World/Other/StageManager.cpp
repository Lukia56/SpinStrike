#include "StageManager.h"
#include <memory>
#include <string>
#include <vector>
#include "Stage/StageLoader.h"

StageManager::StageManager(const std::string& objectDataPath)
{
	std::vector<std::unique_ptr<GameObject>> objects = Stage::StageLoader::Load(objectDataPath);

	for (auto& object : objects)
	{
		AddToChild(std::move(object));
	}
}

void StageManager::Init()
{
}

void StageManager::Update()
{
}
