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

	Collider3D(std::unique_ptr<Collision::IShape3D> shape, GameObject* owner, Collision::Tag tag, bool enable = true, bool isDynamic = true);
	~Collider3D();

	/// <summary>
	/// コライダを有効にし、マネージャーに登録する
	/// </summary>
	void Enable();

	/// <summary>
	/// コライダを無効にし、マネージャーへの登録を解除する
	/// </summary>
	void Disable();

public:

	bool IsEnabled() const { return mIsEnable; }

	void SetDynamic(bool isDynamic) { mIsDynamic = isDynamic; }
	bool IsDynamic() const { return mIsDynamic; }

	Collision::IShape3D* GetShape() const { return mShape.get(); }

	GameObject* GetOwner() const { return mOwner; }

	Collision::Tag GetTag() const { return mTag; }

private:

	bool mIsEnable;

	/// <summary>
	/// もしfalse(= 静的)なら静的なコライダとの衝突を行わなくなる
	/// </summary>
	bool mIsDynamic;

	std::unique_ptr<Collision::IShape3D> mShape;

	GameObject* mOwner;

	Collision::Tag mTag;
};
