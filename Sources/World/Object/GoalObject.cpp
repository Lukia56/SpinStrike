#include "GoalObject.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 100.0f, 200.0f, 100.0f };
	constexpr Vector3 kCollisionOffsetPos{ 0.0f, 100.0f, 0.0f };
}

GoalObject::GoalObject() :
	mCollider(nullptr)
{
}

void GoalObject::Init()
{
	SetTag(Tag::Goal);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kCollisionSize, kCollisionOffsetPos),
		this,
		Collision::Tag::Body,
		true,
		false
	);
}

void GoalObject::Update()
{
	mCollider->Update();
}

void GoalObject::DebugDraw()
{
	mCollider->DebugDraw();
}
