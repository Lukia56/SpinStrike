#include "Collider3D.h"
#include <memory>
#include "Collision/Collision3D.h"
#include "Collision/CollisionManager.h"

Collider3D::Collider3D(std::unique_ptr<Collision::IShape3D> shape, GameObject* owner, Tag tag, bool enable) :
	mIsEnable(enable),
	mShape(std::move(shape)),
	mOwner(owner),
	mTag(tag)
{
	if (enable) CollisionManager::GetInstance().Register(this);
}

Collider3D::~Collider3D()
{
	Disable();
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
