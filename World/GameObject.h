#pragma once

#include <memory>
#include <vector>
#include "Components/Transform.h"
#include "Components/CollisionResult.h"

/// <summary>
/// ゲームで扱うオブジェクトの基底クラス
/// トランスフォームを管理する
/// </summary>
class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;

	virtual void Finalize() {};

	virtual void Update() = 0;

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

	virtual void OnCollision(GameObject* other, const Collision3D::Result& result) {};

public:

	Transform& GetTransform() { return mTransform; }

	bool IsActive() const { return mIsActive; }
	void SetActive(bool flag) { mIsActive = flag; }

protected:

	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T, class... Args>
	requires std::derived_from<T, GameObject>
	T* AddToChild(Args&&... args);

	/// <summary>
	/// ゲームオブジェクトを削除する
	/// 実際の削除は更新処理の後に行われる
	/// </summary>
	void Destroy(GameObject* deleteTarget);

protected:

	Transform mTransform;

private:

	bool mIsCalledDestroy;

	/// <summary>
	/// 更新処理を行うかどうかのフラグ
	/// 非アクティブになるとすべての子オブジェクトも非アクティブになる
	/// </summary>
	bool mIsActive;
};

template <class T, class... Args>
requires std::derived_from<T, GameObject>
inline T* GameObject::AddToChild(Args&&... args)
{
	auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
	ptr->Init();

	T* rawPtr = ptr.get();

	rawPtr->GetTransform().SetupParent(std::move(ptr), &mTransform);

	return rawPtr;
}
