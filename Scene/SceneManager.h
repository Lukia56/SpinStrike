#pragma once

#include <memory>

class SceneBase;

/// <summary>
/// シーンの遷移やライフサイクルの管理をするクラス
/// </summary>
class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	/// <summary>
	/// 初期シーンの作成を行う
	/// </summary>
	void Initialize();

	void Finalize();

	/// <summary>
	/// シーンの更新処理
	/// シーン遷移の判定も行う
	/// </summary>
	void Update();

	void Draw();

	void DebugDraw();

private:

	template <class T>
	requires std::derived_from<T, SceneBase>
	void CreateScene();

private:

	std::unique_ptr<SceneBase> mCurrentScene;
};

template<class T>
requires std::derived_from<T, SceneBase>
inline void SceneManager::CreateScene()
{
	auto scene = std::make_unique<T>();
	scene->Init();
	mCurrentScene = std::move(scene);
}
