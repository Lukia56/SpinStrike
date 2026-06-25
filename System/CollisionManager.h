#pragma once

#include <vector>

class GameObject;

/// <summary>
/// 衝突を検知し結果を送信するクラス
/// </summary>
class CollisionManager
{
private:

	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator=(CollisionManager&&) = delete;

public:

	~CollisionManager();

	void CheckAllCollision();

	void Register(GameObject* object);

	void Unregister(GameObject* object);

	static CollisionManager& GetInstance();

private:

	std::vector<GameObject*> mObjects;
};
