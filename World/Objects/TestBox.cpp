#include "TestBox.h"
#include <memory>
#include "../Components/Collision3D.h"
#include "System/CollisionManager.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 200.0f, 200.0f, 200.0f };
}

TestBox::TestBox()
{
	mCollider = std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize);
	CollisionManager::GetInstance().Register(this, mCollider.get(), Collision::Tag::Terrain);
}

TestBox::~TestBox()
{
	CollisionManager::GetInstance().Unregister(mCollider.get());
}

void TestBox::Init()
{
}

void TestBox::Finalize()
{
}

void TestBox::Update()
{
	mCollider->SetPosition(mTransform.CalculateWorldPosition());
}

void TestBox::Draw()
{
}

void TestBox::DebugDraw()
{
	mCollider->DebugDraw();
}
