#pragma once

#include <memory>

namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// DXライブラリのモデルデータには様々な情報が入っており、
/// 複数オブジェクトで共有できないため、モデルハンドルを複製して管理する
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
