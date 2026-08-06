#include "Application.h"
#include <chrono>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include <Psapi.h>
#include "Scene/SceneManager.h"
#include "System/EffekseerManager.h"
#include "System/ImGuiRenderer.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/TimeManager.h"
#include "Utility/Random.h"
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kWindowConfigPath = "Resources\\MasterData\\WindowConfigs.csv";
}

Application::Application() :
	mSceneManager(nullptr),
	mEffekseerManager(nullptr),
	mImGuiRenderer(nullptr)
{
}

Application::~Application()
{
}

bool Application::Initialize()
{
	bool result;
	
	result = InitDxLib();
	if (!result) return false;

	mEffekseerManager = std::make_unique<EffekseerManager>();
	result = mEffekseerManager->Initialize();
	if (!result) return false;

	mSceneManager = std::make_unique<SceneManager>();
	mSceneManager->Initialize();

	mImGuiRenderer = std::make_unique<ImGuiRenderer>();
	mImGuiRenderer->Initialize();

	TimeManager::Initialize();

	InputManager::GetInstance().Initialize();

	ResourceManager::GetInstance().Init();

	Random::Init();

	// ここまで問題が起きなかったらtrue
	return true;
}

void Application::Finalize()
{
	// メンバの後処理
	mImGuiRenderer->Finalize();
	mSceneManager->Finalize();

	ResourceManager::GetInstance().Finalize();

	mEffekseerManager->Finalize();

	// メモリリークが起きる可能性があるため最後に呼ぶ
	DxLib_End();
}

void Application::GameLoop()
{
	// 問題が起きない限り処理を繰り返す
	while (ProcessMessage() == 0)
	{
		ProcessInput();
		Update();
		ProcessOutput();

#ifdef _DEBUG
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
#endif
	}
}

void Application::ProcessInput()
{
	InputManager::GetInstance().Update();
}

void Application::Update()
{
	using namespace std::chrono;
	while (duration_cast<microseconds>(steady_clock::now() - TimeManager::GetPrevTime()) < microseconds(TimeManager::GetFixedDeltaTimeMs())) {}
	TimeManager::Update();

	mSceneManager->PhysicsUpdate();

	mSceneManager->Update();

	mEffekseerManager->Update();
}

void Application::ProcessOutput()
{
	// 描画
	ClearDrawScreen();
	clsDx();

	mSceneManager->Draw();
	mEffekseerManager->Draw();

#ifdef _DEBUG
	mImGuiRenderer->Draw([this]()
		{
			if (ImGui::Begin("System"))
			{
				ImGui::Text("RealFPS %.1f", 1.0f / TimeManager::GetRawDeltaTime());

				PROCESS_MEMORY_COUNTERS_EX pmc;
				GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
				ImGui::Text("Memory %.3f MB", pmc.WorkingSetSize / 1024.0f / 1024.0f);

				ImGui::End();
			}

			mSceneManager->DebugDraw();
		});
#endif

	// 画面に表示
	ScreenFlip();
}

bool Application::InitDxLib()
{
	// ログ出力設定
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(true);
#else
	SetOutApplicationLogValidFlag(false);
#endif

	WindowConfigs windowConfigs = Data::Csv::LoadCsvAs<WindowConfigs>(kWindowConfigPath)[0];
	SetMainWindowText(windowConfigs.windowText.c_str());
	SetGraphMode(windowConfigs.width, windowConfigs.height, windowConfigs.colorBit);

	// ウィンドウをタイトルバーなし、枠なしに設定する
	SetWindowStyleMode(2);

	ChangeWindowMode(true);

	SetWaitVSyncFlag(false);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1) return false;

	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(false);
	SetBackgroundColor(128, 128, 128);

	SetChangeScreenModeGraphicsSystemResetFlag(false);

	return true;
}
