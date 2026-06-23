#pragma once

#include <functional>

/// <summary>
/// ImGuiを管理して描画するクラス
/// </summary>
class ImGuiRenderer
{
public:

	ImGuiRenderer() = default;
	~ImGuiRenderer() = default;

	void Initialize();

	void Finalize();

	/// <summary>
	/// ImGui描画処理
	/// </summary>
	/// <param name="func">ImGuiのウィンドウ描画関数</param>
	void Draw(std::function<void(void)> func);
};
