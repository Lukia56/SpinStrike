#pragma once

#include <memory>
#include <vector>
#include "Utility/Math.h"
#include "Utility/Vector.h"

class GameObject;

/// <summary>
/// 位置、回転、拡縮とゲームオブジェクトの階層構造を管理するクラス
/// </summary>
class Transform
{
public:

	using GameObjectContainer = std::vector<std::unique_ptr<GameObject>>;

	/// <summary>
	/// 親からの相対座標
	/// </summary>
	Vector3 localPosition;
	/// <summary>
	/// 親からの相対角度
	/// </summary>
	Vector3 localRotation;
	/// <summary>
	/// 親からの相対スケール
	/// </summary>
	Vector3 localScale;

public:

	Transform(GameObject* owner);
	~Transform();

	void Translate(const Vector3& translation);

	void RotateRad(const Vector3& angle);
	void RotateDeg(const Vector3& angle);

	/// <summary>
	/// まだ親が設定されていない場合にのみ使用
	/// </summary>
	void SetupParent(std::unique_ptr<GameObject> owner, Transform* newParent);

	/// <summary>
	/// すでに親が設定されている場合にのみ使用
	/// nullptrを指定したら所有者を解放する
	/// </summary>
	void ChangeParent(Transform* newParent);

	/// <summary>
	/// 親オブジェクトについて再帰し、ワールド座標を取得する
	/// </summary>
	Vector3 CalculateWorldPosition() const;

	/// <summary>
	/// 親オブジェクトについて再帰し、ワールド角度を取得する
	/// </summary>
	Vector3 CalculateWorldRotation() const;

	/// <summary>
	/// 親オブジェクトについて再帰し、ワールドスケールを取得する
	/// </summary>
	Vector3 CalculateWorldScale() const;

public:
	
	Vector3 GetRotationAsDeg() const;
	void SetRotationAsDeg(const Vector3& angle);

	GameObjectContainer& GetChildren() { return mChildren; }

	Transform* GetParent() const { return mParent; }

private:

	GameObjectContainer mChildren;

	Transform* mParent;

	GameObject* mOwner;
};
