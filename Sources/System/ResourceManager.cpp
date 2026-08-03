#include "ResourceManager.h"
#include <DxLib.h>
#include "Resource/Resource.h"

void ResourceManager::Init()
{
}

void ResourceManager::Finalize()
{
	ReleaseAll();
}

void ResourceManager::ReleaseAll()
{
	for (auto& it : mResourceTable)
	{
		if (it.second->GetHandle() == -1) continue;

		it.second->Delete();
	}
	mResourceTable.clear();
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;

	return instance;
}
