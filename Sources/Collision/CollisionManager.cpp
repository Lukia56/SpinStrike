#include "CollisionManager.h"
#include <algorithm>
#include "Collision/Collision3D.h"
#include "World/Component/Collider3D.h"
#include "World/GameObject.h"

void CollisionManager::CheckAllCollision()
{
	for (size_t i = 0; i < mColliders.size(); i++)
	{
		const Collider3D* colliderA = mColliders[i];
		if (!colliderA) continue;

		GameObject* ownerA = colliderA->GetOwner();
		if (!ownerA) continue;
		if (!ownerA->IsActive()) continue;

		for (size_t j = i + 1; j < mColliders.size(); j++)
		{
			const Collider3D* colliderB = mColliders[j];
			if (!colliderB) continue;

			// お互いが静的なら衝突を調べない
			if (!colliderA->IsDynamic() && !colliderB->IsDynamic()) continue;

			GameObject* ownerB = colliderB->GetOwner();
			if (!ownerB) continue;
			if (!ownerB->IsActive()) continue;

			if (ownerA == ownerB) continue;

			// 衝突結果を調べる
			Collision::Result result = colliderA->GetShape()->CheckCollision(colliderB->GetShape());
			if (!result.isHit) continue;

			ownerA->ResolveCollision(result, colliderA, colliderB);

			// もう一つのコライダ目線に合わせて法線を反転
			result.normal = -result.normal;

			ownerB->ResolveCollision(result, colliderB, colliderA);
		}
	}
}

std::vector<Collision::RaycastResult> CollisionManager::Raycast(const Collision::Ray& ray)
{
	return Raycast(ray, [](Collider3D*) { return true; });
}

std::vector<Collision::RaycastResult> CollisionManager::Raycast(const Collision::Ray& ray, std::function<bool(Collider3D*)> pred)
{
	std::vector<Collision::RaycastResult> results;

	for (const auto& collider : mColliders)
	{
		if (!pred(collider)) continue;

		Collision::RaycastResult result = collider->GetShape()->Raycast(ray);

		if (!result.isHit) continue;

		results.emplace_back(result);
	}

	// 距離の昇順に並び替え
	std::sort(results.begin(), results.end(), [](const Collision::RaycastResult& a, const Collision::RaycastResult& b)
		{
			return a.distance < b.distance;
		});

	return results;
}

void CollisionManager::Register(Collider3D* collider)
{
	mColliders.emplace_back(collider);
}

void CollisionManager::Unregister(Collider3D* collider)
{
	auto iter = std::find(mColliders.begin(), mColliders.end(), collider);

	// 配列に存在しないなら早期リターン
	if (iter == mColliders.end()) return;

	// 配列から削除
	std::iter_swap(iter, mColliders.end() - 1);
	mColliders.pop_back();
}

CollisionManager& CollisionManager::GetInstance()
{
	static CollisionManager instance;

	return instance;
}
