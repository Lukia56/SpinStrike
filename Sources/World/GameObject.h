#pragma once

#include <memory>
#include <vector>
#include "Collision/CollisionResult.h"
#include "Component/Transform.h"

class Collider3D;

/// <summary>
/// ゲームで扱うオブジェクトの基底クラス
/// トランスフォームを管理する
/// </summary>
class GameObject
{
public:

	GameObject();
	GameObject(std::unique_ptr<Transform> transform);
	virtual ~GameObject();

	enum class Tag
	{
		None,
		Player,
		Terrain,
		Tornado,
		Enemy,
	};

	virtual void Init() = 0;

	virtual void Finalize() {};

	virtual void Update() = 0;

	virtual void PhysicsUpdate() {};

	virtual void Draw() {};

	/// <summary>
	/// ImGuiなどのデバッグ用描画処理
	/// </summary>
	virtual void DebugDraw() {};

	/// <summary>
	/// 削除処理が呼ばれているかチェックし
	/// 呼ばれていたら削除を行う
	/// </summary>
	/// <returns>自身を削除するならtrue</returns>
	bool CheckDestroy();

	virtual void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) {}

	/// <summary>
	/// オブジェクトを生成して子オブジェクトに追加する
	/// </summary>
	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T, class... Args>
	requires std::derived_from<T, GameObject>
	T* CreateToChild(Args&&... args);
	
	/// <summary>
	/// 生成済みのオブジェクトを子オブジェクトに追加する
	/// </summary>
	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T>
	requires std::derived_from<T, GameObject>
	T* AddToChild(std::unique_ptr<T> object);

	/// <summary>
	/// ゲームオブジェクトを削除する
	/// 実際の削除は更新処理の後に行われる
	/// </summary>
	void Destroy(GameObject* deleteTarget);

public:

	Transform* GetTransform() const { return mTransform.get(); }

	bool IsActive() const { return mIsActive; }
	virtual void SetActive(bool flag) { mIsActive = flag; }

	Tag GetTag() const { return mTag; }
	void SetTag(Tag tag) { mTag = tag; }

protected:

	std::unique_ptr<Transform> mTransform;

private:

	bool mIsCalledDestroy;

	/// <summary>
	/// 更新処理を行うかどうかのフラグ
	/// 非アクティブになるとすべての子オブジェクトも非アクティブになる
	/// </summary>
	bool mIsActive;

	Tag mTag;
};

template <class T, class... Args>
requires std::derived_from<T, GameObject>
inline T* GameObject::CreateToChild(Args&&... args)
{
	auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
	ptr->Init();

	T* rawPtr = ptr.get();

	rawPtr->GetTransform()->SetupParent(std::move(ptr), mTransform.get());

	return rawPtr;
}

template<class T>
requires std::derived_from<T, GameObject>
inline T* GameObject::AddToChild(std::unique_ptr<T> object)
{
	if (!object) return nullptr;

	object->Init();

	T* rawPtr = object.get();

	rawPtr->GetTransform()->SetupParent(std::move(object), mTransform.get());

	return rawPtr;
}
