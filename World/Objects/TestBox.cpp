#include "TestBox.h"
#include <memory>
#include "../Components/Collider3D.h"
#include "Collision/Collision3D.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 200.0f, 200.0f, 200.0f };
}

TestBox::TestBox()
{
	SetTag(Tag::Terrain);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize),
		this,
		Collider3D::Tag::Body
	);
}

TestBox::TestBox(const Vector3& scale)
{
	SetTag(Tag::Terrain);

	mTransform.localScale = scale;
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, scale),
		this,
		Collider3D::Tag::Body
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
	mCollider->GetShape()->SetPosition(mTransform.CalculateWorldPosition());
}

void TestBox::Draw()
{
}

void TestBox::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}
