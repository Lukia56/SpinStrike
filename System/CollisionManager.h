#pragma once

#include <vector>
#include "Collision/CollisionTag.h"

class GameObject;
namespace Collision
{
	class ICollider3D;
}

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

	void Register(GameObject* owner, Collision::ICollider3D* collider, Collision::Tag tag = Collision::Tag::None);

	void Unregister(Collision::ICollider3D* collider);

	static CollisionManager& GetInstance();

private:

	struct CollisionActor
	{
		GameObject* owner = nullptr;
		Collision::ICollider3D* collider = nullptr;
		Collision::Tag tag;
	};

private:

	std::vector<CollisionActor> mCollisionActors;
};
