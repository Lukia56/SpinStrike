#include "TestBox.h"
#include <memory>
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 200.0f, 200.0f, 200.0f };
}

TestBox::TestBox()
{
	SetTag(Tag::Terrain);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kCollisionSize),
		this,
		Collision::Tag::Body
	);
}

TestBox::TestBox(const Vector3& scale)
{
	SetTag(Tag::Terrain);

	mTransform->localScale = scale;
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(scale),
		this,
		Collision::Tag::Body
	);
}

TestBox::~TestBox()
{
}

void TestBox::Init()
{
}

void TestBox::Finalize()
{
}

void TestBox::Update()
{
	mCollider->GetShape()->SetPosition(mTransform->CalculateWorldPosition());
}

void TestBox::Draw()
{
}

void TestBox::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}
