#pragma once

#include <memory>
#include <vector>

class GameObject;
class CameraManager;

/// <summary>
/// シーンの基礎となるクラス
/// ゲームオブジェクトの更新やライフサイクルの管理を行う
/// </summary>
class SceneBase
{
public:

	using GameObjectContainer = std::vector<std::unique_ptr<GameObject>>;

	SceneBase();
	virtual ~SceneBase();

	virtual void Init() = 0;
	virtual void Finalize() = 0;

	/// <returns>次のシーンのポインタ</returns>
	std::unique_ptr<SceneBase> UpdateBase();
	void DrawBase();

public:

	CameraManager* GetCameraManager() const { return mCameraManager.get(); }

protected:

	/// <summary>
	/// 派生の更新処理
	/// </summary>
	/// <returns>次のシーンのポインタ</returns>
	virtual std::unique_ptr<SceneBase> Update() = 0;

	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T>
	requires std::derived_from<T, GameObject>
	T* AddToRoot(std::unique_ptr<T> root);

private:

	void UpdateRootObjects();
	void DrawRootObjects();

	void UpdateGameObject(GameObject* gameObject);
	void DrawGameObject(GameObject* gameObject);

private:
	
	GameObjectContainer mRootObjects;

	std::unique_ptr<CameraManager> mCameraManager;
};

template <class T>
requires std::derived_from<T, GameObject>
inline T* SceneBase::AddToRoot(std::unique_ptr<T> root)
{
	T* ptr = root.get();
	ptr->Init();
	mRootObjects.emplace_back(std::move(root));
	return ptr;
}
