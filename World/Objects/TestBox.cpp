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
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize),
		this,
		Collision::Tag::Terrain
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
