#include "ImGuiRenderer.h"
#include <DxLib.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// ImGuiにプロシージャの情報を流す
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
	{
		return true;
	}
	return 0;
}

void ImGuiRenderer::Initialize()
{
	// DxLibが持つDirectXの情報を取得する
	ID3D11Device* device = (ID3D11Device*)(GetUseDirect3D11Device());
	ID3D11DeviceContext* context = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();

	// ImGuiを初期化
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(device, context);

	// フォントの初期化
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();

	// ウインドウプロージャを登録する
	SetHookWinProc(WndProc);
}

void ImGuiRenderer::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::Draw(std::function<void(void)> func)
{
	// 描画準備
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_::ImGuiCol_WindowBg].w = 0.5f;

	// 描画処理
	func();

	// 描画データを表示する
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
