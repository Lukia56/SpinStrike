#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// <para>リソースの多重ロードを防止するための管理クラス</para>
/// <para>どこからも参照されなくなったリソースは自動で解放される</para>
/// </summary>
class ResourceManager
{
private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

public:

	~ResourceManager() = default;

	void Initialize();
	void Finalize();

	/// <summary>
	/// リソースを取得する
	/// 初回呼び出し時は読み込んで取得
	/// 2回目以降は取得のみ
	/// </summary>
	template <class T>
	requires std::derived_from<T, Resource::ResourceBase>
	std::shared_ptr<Resource::ResourceBase> GetResource(const std::string& path);

	/// <summary>
	/// リソーステーブルからリソースを削除する
	/// リソースの解放は参照カウンタが0になったときのみ
	/// </summary>
	void DeleteResource(const std::string& path);

	static ResourceManager& GetInstance();

private:

	std::unordered_map<std::string, std::weak_ptr<Resource::ResourceBase>> mResourceTable;
};

template<class T>
requires std::derived_from<T, Resource::ResourceBase>
inline std::shared_ptr<Resource::ResourceBase> ResourceManager::GetResource(const std::string& path)
{
	// 初回読み込み
	if (!mResourceTable.contains(path))
	{
		std::shared_ptr<Resource::ResourceBase> resource = std::make_shared<T>(path);

		// 読み込みに失敗したらnullptrを返す
		if (!resource->Load())
		{
			assert(false && "ResourceManager // リソースの読み込みに失敗しました");
			return nullptr;
		}
		
		// weak_ptrをテーブルに
		mResourceTable.try_emplace(path, resource);

		return resource;
	}

	return mResourceTable.at(path).lock();
}
