#pragma once

#include <memory>

class SceneManager;
class ImGuiRenderer;

/// <summary>
/// アプリ全体で必要なものを管理して、
/// ゲームループを行うクラス
/// </summary>
class Application
{
public:

	Application();
	~Application();

	/// <summary>
	/// アプリを初期化する
	/// </summary>
	/// <returns>初期化に成功したらtrue、失敗したらfalse</returns>
	bool Initialize();

	/// <summary>
	/// アプリを終了する
	/// </summary>
	void Finalize();

	/// <summary>
	/// ゲームループ
	/// ゲームの更新処理を行う
	/// </summary>
	void GameLoop();

private:

	void ProcessInput();
	void Update();
	void ProcessOutput();

private:

	std::unique_ptr<SceneManager> mSceneManager;

	std::unique_ptr<ImGuiRenderer> mImGuiRenderer;
};
