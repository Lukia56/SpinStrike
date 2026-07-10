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

	~CollisionManager() = default;

	/// <summary>
	/// <para>登録されたすべてのコライダ同士の衝突を調べる</para>
	/// <para>所有者が非アクティブであったり、お互いの所有者が同じなら調べない</para>
	/// </summary>
	void CheckAllCollision();

	void Register(Collider3D* collider);

	void Unregister(Collider3D* collider);

	static CollisionManager& GetInstance();

private:

	std::vector<Collider3D*> mColliders;
};
