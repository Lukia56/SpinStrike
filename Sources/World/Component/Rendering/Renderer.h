#pragma once

#include <cassert>
#include <string>
#include "System/ResourceManager.h"
#include "System/Resource/ResourceBase.h"
#include "Utility/Vector.h"

class GameObject;

/// <summary>
/// グラフィックリソースの描画を行う基底
/// </summary>
template<class T>
requires std::derived_from<T, Resource::ResourceBase>
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

public:

	void SetOffsetPos(const Vector3& offsetPos) { mOffsetPos = offsetPos; }

protected:

	Resource::ResourceBase* mResource;

	GameObject* mOwner;

	Vector3 mOffsetPos;
};
