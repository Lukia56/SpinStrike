#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

class Resource;

/// <summary>
/// リソースの多重ロードを防止するための管理クラス
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

	void Init();
	void Finalize();

	/// <summary>
	/// 画像を取得する
	/// 初回呼び出し時は読み込んで取得
	/// 2回目以降は取得のみ
	/// </summary>
	template <class T>
	requires std::derived_from<T, Resource>
	Resource* GetResource(const std::string& path);

	/// <summary>
	/// 現在読み込んでいるすべてのリソースを解放する
	/// </summary>
	void ReleaseAll();

	static ResourceManager& GetInstance();

private:

	std::unordered_map<std::string, std::unique_ptr<Resource>> mResourceTable;
};

template<class T>
requires std::derived_from<T, Resource>
inline Resource* ResourceManager::GetResource(const std::string& path)
{
	// 初回読み込み
	if (!mResourceTable.contains(path))
	{
		std::unique_ptr<Resource> resource = std::make_unique<T>();

		// 読み込みに失敗したらnullptrを返す
		if (!resource->Load(path))
		{
			assert(false && "ResourceManager // リソースの読み込みに失敗しました");
			return nullptr;
		}
		
		Resource* ptr = resource.get();

		mResourceTable.emplace(path, std::move(resource));

		return ptr;
	}

	return mResourceTable.at(path).get();
}
