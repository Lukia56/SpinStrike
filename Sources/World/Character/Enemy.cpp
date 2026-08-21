#include "Enemy.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 50.0f, 50.0f, 50.0f };
}

Enemy::Enemy() :
	mCollider(nullptr)
{
	mCollider = std::make_unique<Collider3D>(
				std::make_unique<Collision::AABB3D>(kCollisionSize),
				this,
				Collision::Tag::Body);
}

void Enemy::Init()
{
}

void Enemy::Finalize()
{
}

void Enemy::PhysicsUpdate()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}

void Enemy::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
}
