#include "CollisionManager.h"
#include <algorithm>
#include "World/Components/Collision3D.h"
#include "World/GameObject.h"

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckAllCollision()
{
	for (const auto& actor : mCollisionActors)
	{
		for (const auto& otherActor : mCollisionActors)
		{
			if (actor.collider == otherActor.collider) continue;

			Collision::Result result = actor.collider->CheckCollision(otherActor.collider);

			if (!result.isHit) continue;

			actor.owner->OnCollision(otherActor.owner, result, otherActor.tag);
		}
	}
}

void CollisionManager::Register(GameObject* owner, Collision::ICollider3D* collider, Collision::Tag tag)
{
	mCollisionActors.emplace_back(CollisionActor{ .owner = owner, .collider = collider, .tag = tag });
}

void CollisionManager::Unregister(Collision::ICollider3D* collider)
{
	auto iter = std::find_if(mCollisionActors.begin(), mCollisionActors.end(),
		[&](const CollisionActor& actor) { return actor.collider == collider; });

	// 配列に存在しないなら早期リターン
	if (iter == mCollisionActors.end()) return;

	// 配列から削除
	std::iter_swap(iter, mCollisionActors.end() - 1);
	mCollisionActors.pop_back();
}

CollisionManager& CollisionManager::GetInstance()
{
	static CollisionManager instance;

	return instance;
}
