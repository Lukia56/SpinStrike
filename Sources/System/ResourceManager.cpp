#include "ResourceManager.h"
#include <DxLib.h>
#include "Resource/ResourceBase.h"

void ResourceManager::Initialize()
{
}

void ResourceManager::Finalize()
{
	mResourceTable.clear();
}

void ResourceManager::DeleteResource(const std::string& path)
{
	if (mResourceTable.empty()) return;
	if (!mResourceTable.contains(path)) return;

	mResourceTable.erase(path);
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;

	return instance;
}
