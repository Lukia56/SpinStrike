#pragma once

#include <memory>

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

	enum class Tag
	{
		Body,
		Foot,
		Sensor
	};

public:

	Collider3D(std::unique_ptr<Collision::IShape3D> shape, GameObject* owner, Tag tag, bool enable = true);
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

	Collision::IShape3D* GetShape() const { return mShape.get(); }

	GameObject* GetOwner() const { return mOwner; }

	Tag GetTag() const { return mTag; }

private:

	bool mIsEnable;

	std::unique_ptr<Collision::IShape3D> mShape;

	GameObject* mOwner;

	Tag mTag;
};
