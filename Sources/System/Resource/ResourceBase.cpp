#include "ResourceBase.h"
#include "../ResourceManager.h"

namespace Resource
{
	ResourceBase::ResourceBase(const std::string& path) :
		mHandle(-1),
		mPath(path)
	{
	}

	ResourceBase::~ResourceBase()
	{
		ResourceManager::GetInstance().DeleteResource(mPath);
	}
}
