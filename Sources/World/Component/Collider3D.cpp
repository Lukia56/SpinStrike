#include "Collider3D.h"
#include <memory>
#include "Collision/Collision3D.h"
#include "Collision/CollisionManager.h"
#include "World/GameObject.h"

Collider3D::Collider3D(std::unique_ptr<Collision::IShape3D> shape, GameObject* owner, Collision::Tag tag, bool enable, bool isDynamic) :
	mIsEnable(enable),
	mIsDynamic(isDynamic),
	mShape(std::move(shape)),
	mOwner(owner),
	mTag(tag)
{
	if (enable) CollisionManager::GetInstance().Register(this);
}

Collider3D::~Collider3D()
{
	CollisionManager::GetInstance().Unregister(this);
}

void Collider3D::Update()
{
	if (!mIsEnable) return;

	Vector3 pos = mOwner->GetTransform()->CalculateWorldPosition();

	mShape->SetPosition(pos);
}

void Collider3D::DebugDraw(const Color& color)
{
	if (!mIsEnable) return;

	mShape->DebugDraw(color);
}

void Collider3D::Enable()
{
	if (mIsEnable) return;
	mIsEnable = true;

	CollisionManager::GetInstance().Register(this);
}

void Collider3D::Disable()
{
	if (!mIsEnable) return;
	mIsEnable = false;

	CollisionManager::GetInstance().Unregister(this);
}
