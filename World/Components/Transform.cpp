#include "Transform.h"
#include <cassert>
#include <memory>
#include <vector>
#include "../GameObject.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

Transform::Transform(GameObject* owner) :
	localPosition(Vector3::Zero),
	localRotation(Vector3::Zero),
	localScale(Vector3::One),
	mOwner(owner),
	mParent(nullptr)
{
}

Transform::~Transform()
{
	// 子オブジェクトを削除する
	while (mChildren.size() > 0)
	{
		auto it = mChildren.begin();
		(*it)->Finalize();
		mChildren.erase(it);
	}

	mParent = nullptr;
	mOwner = nullptr;
}

void Transform::Translate(const Vector3& translation)
{
	localPosition += translation;
}

void Transform::RotateRad(const Vector3& angle)
{
	localRotation += angle;
}

void Transform::RotateDeg(const Vector3& angle)
{
	localRotation += Vector3(
		Math::ToRadian(angle.x),
		Math::ToRadian(angle.y),
		Math::ToRadian(angle.z)
	);
}

void Transform::SetupParent(std::unique_ptr<GameObject> owner, Transform* newParent)
{
	if (mParent)
	{
		assert(false && "Transform // すでに親オブジェクトが設定されています");
		return;
	}

	// 親を設定
	mParent = newParent;

	// 新しい親に移動
	if (mParent)
	{
		mParent->GetChildren().emplace_back(std::move(owner));
	}
}

void Transform::ChangeParent(Transform* newParent)
{
	if (!mParent)
	{
		assert(false && "Transform // 親オブジェクトが設定されていません");
		return;
	}

	// 自身のイテレータを探す
	auto& siblings = mParent->GetChildren();
	auto it = std::find_if(siblings.begin(), siblings.end(),
		[this](const std::unique_ptr<GameObject>& ptr)
		{
			return this == &ptr->GetTransform();
		});
	if (it == siblings.end())
	{
		assert(false && "Transform // 親オブジェクトに自身が含まれていませんでした");
		return;
	}

	// 元の親から削除
	auto gameObject = std::move(*it);
	siblings.erase(it);

	// 親を設定
	mParent = newParent;

	// 新しい親に移動
	if (mParent)
	{
		mParent->GetChildren().emplace_back(std::move(gameObject));
	}
}

Vector3 Transform::CalculateWorldPosition() const
{
	Vector3 world = localPosition;

	// 親オブジェクトについて再帰
	if (mParent) return world += mParent->CalculateWorldPosition();

	return world;
}

Vector3 Transform::CalculateWorldRotation() const
{
	Vector3 world = localRotation;

	// 親オブジェクトについて再帰
	if (mParent) world += mParent->CalculateWorldRotation();

	return world;
}

Vector3 Transform::CalculateWorldScale() const
{
	Vector3 world = localScale;

	// 親オブジェクトについて再帰
	if (mParent) world += mParent->CalculateWorldScale();

	return world;
}

Vector3 Transform::GetRotationAsDeg() const
{
	return Vector3(
		Math::ToRadian(localRotation.x),
		Math::ToRadian(localRotation.y),
		Math::ToRadian(localRotation.z)
	);
}

void Transform::SetRotationAsDeg(const Vector3& angle)
{
	localRotation = Vector3(
		Math::ToRadian(angle.x),
		Math::ToRadian(angle.y),
		Math::ToRadian(angle.z)
	);
}
