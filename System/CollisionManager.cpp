#include "CollisionManager.h"
#include <algorithm>
#include "World/GameObject.h"

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckAllCollision()
{
	for (const auto& it : mObjects)
	{
		
	}
}

void CollisionManager::Register(GameObject* object)
{
	mObjects.emplace_back(object);
}

void CollisionManager::Unregister(GameObject* object)
{
	auto iter = std::find(mObjects.begin(), mObjects.end(), object);

	// 配列に存在しないなら早期リターン
	if (iter == mObjects.end()) return;

	// 配列から削除
	std::iter_swap(iter, mObjects.end() - 1);
	mObjects.pop_back();
}
