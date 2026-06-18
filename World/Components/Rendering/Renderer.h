#pragma once

#include <cassert>
#include <string>
#include "System/ResourceManager.h"
#include "System/Resource/Resource.h"

class GameObject;

/// <summary>
/// グラフィックリソースの描画を行う基底
/// </summary>
template<class T>
requires std::derived_from<T, Resource>
class Renderer
{
public:

	Renderer(GameObject* owner) : mResource(nullptr), mOwner(owner) {}
	virtual ~Renderer()
	{
		mResource = nullptr;
		mOwner = nullptr;
	}

	/// <summary>
	/// クラスのテンプレート引数のリソースの読み込みを行う
	/// </summary>
	virtual void Load(const std::string& filePath)
	{
		mResource = ResourceManager::GetInstance().GetResource<T>(filePath);
	}

	/// <summary>
	/// リソースの描画処理を実装する
	/// </summary>
	virtual void Draw() = 0;

protected:

	Resource* mResource;

	GameObject* mOwner;
};
