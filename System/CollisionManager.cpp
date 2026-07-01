#include "CollisionManager.h"
#include <algorithm>
#include "World/Components/Collision3D.h"
#include "World/GameObject.h"

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckAllCollision()
{
	for (size_t i = 0; i < mCollisionActors.size(); i++)
	{
		CollisionActor& actorA = mCollisionActors[i];

		if (!actorA.owner->IsActive()) continue;

		for (size_t j = i + 1; j < mCollisionActors.size(); j++)
		{
			CollisionActor& actorB = mCollisionActors[j];

			if (!actorB.owner->IsActive()) continue;

			Collision::Result result = actorA.collider->CheckCollision(actorB.collider);

			if (!result.isHit) continue;

			actorA.owner->OnCollision(actorB.owner, result, actorB.tag);

			// もう一つのコリジョン目線に合わせて法線を反転
			result.normal = -result.normal;

			actorB.owner->OnCollision(actorA.owner, result, actorA.tag);
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
