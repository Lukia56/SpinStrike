#pragma once

#include <vector>
#include "Collision/CollisionTag.h"

class GameObject;
namespace Collision
{
	class IShape3D;
}
class Collider3D;

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

	void Register(Collider3D* collider);

	void Unregister(Collider3D* collider);

	static CollisionManager& GetInstance();

private:

	std::vector<Collider3D*> mColliders;
};
