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

	void Init();
	void Finalize();

	std::unique_ptr<SceneBase> Update();
	void PhysicsUpdate();

	void Draw();
	void DebugDraw();

public:

	CameraManager* GetCameraManager() const { return mCameraManager.get(); }

protected:

	/// <summary>
	/// 派生の初期化処理
	/// </summary>
	virtual void OnInit() = 0;

	/// <summary>
	/// 派生の終了処理
	/// </summary>
	virtual void OnFinalize() {}

	/// <summary>
	/// 派生の更新処理
	/// </summary>
	/// <returns>次のシーンのポインタ</returns>
	virtual std::unique_ptr<SceneBase> OnUpdate() = 0;

	/// <summary>
	/// 派生の描画処理
	/// テスト用
	/// </summary>
	virtual void OnDraw() {};

	/// <summary>
	/// 派生のデバッグ描画処理
	/// テスト用
	/// </summary>
	virtual void OnDebugDraw() {}

	/// <summary>
	/// オブジェクトを生成してルートオブジェクトに追加する
	/// </summary>
	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T, class... Args>
	requires std::derived_from<T, GameObject>
	T* CreateToRoot(Args&&... args);
	
	/// <summary>
	/// 生成済みのオブジェクトをルートに追加する
	/// </summary>
	/// <returns>追加したゲームオブジェクトの生ポインタ</returns>
	template <class T>
	requires std::derived_from<T, GameObject>
	T* AddToRoot(std::unique_ptr<T> object);

private:

	void UpdateRootObjects();
	void PhysicsUpdateRootObjects();
	void DrawRootObjects();
	void DebugDrawRootObjects();

	void UpdateGameObject(GameObject* gameObject);
	void PhysicsUpdateGameObject(GameObject* gameObject);
	void DrawGameObject(GameObject* gameObject);
	void DebugDrawGameObject(GameObject* gameObject);

private:
	
	GameObjectContainer mRootObjects;

	std::unique_ptr<CameraManager> mCameraManager;
};

template<class T, class ...Args>
requires std::derived_from<T, GameObject>
inline T* SceneBase::CreateToRoot(Args&&... args)
{
	auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
	ptr->Init();

	T* rawPtr = ptr.get();

	mRootObjects.emplace_back(std::move(ptr));

	return rawPtr;
}

template<class T>
requires std::derived_from<T, GameObject>
inline T* SceneBase::AddToRoot(std::unique_ptr<T> object)
{
	if (!object) return nullptr;

	object->Init();

	T* rawPtr = object.get();

	mRootObjects.emplace_back(std::move(object));

	return rawPtr;
}
