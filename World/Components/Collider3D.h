#pragma once

#include <memory>
#include "Collision/CollisionTag.h"

class GameObject;
namespace Collision
{
	class IShape3D;
}

/// <summary>
/// 衝突データの管理、マネージャーへの登録を行う
/// </summary>
class Collider3D
{
public:

	Collider3D(std::unique_ptr<Collision::IShape3D> shape, GameObject* owner, Collision::Tag tag);
	~Collider3D();

	void Enable();

	void Disable();

public:

	Collision::IShape3D* GetShape() const { return mShape.get(); }

	GameObject* GetOwner() const { return mOwner; }

	Collision::Tag GetTag() const { return mTag; }

private:

	bool mIsEnable;

	std::unique_ptr<Collision::IShape3D> mShape;

	GameObject* mOwner;

	Collision::Tag mTag;
};
