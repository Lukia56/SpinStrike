#pragma once

#include <memory>

namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// DXライブラリのモデルハンドルを複製して管理する
/// </summary>
class ModelInstance
{
public:

	ModelInstance(std::shared_ptr<Resource::ResourceBase> resource);
	~ModelInstance();

	int GetHandle() const { return mDuplicatedHandle; }

private:

	int mDuplicatedHandle;
};
