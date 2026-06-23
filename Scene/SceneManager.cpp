#include "SceneManager.h"
#include <memory>
#include "SceneBase.h"
#include "SceneInit.h"
#include "Camera/CameraManager.h"

SceneManager::SceneManager() :
	mCurrentScene(nullptr)
{
}

SceneManager::~SceneManager() = default;

void SceneManager::Initialize()
{
	// 初期シーンの作成
	CreateScene<SceneInit>();
}

void SceneManager::Finalize()
{
	mCurrentScene->Finalize();
	mCurrentScene.reset();
}

void SceneManager::Update()
{
	auto nextScene = mCurrentScene->UpdateBase();
	if (nextScene == nullptr) return;

	// シーンを切り替える
	mCurrentScene->Finalize();
	mCurrentScene = std::move(nextScene);
	mCurrentScene->Init();
}

void SceneManager::Draw()
{
	mCurrentScene->DrawBase();
}

void SceneManager::DebugDraw()
{
	mCurrentScene->DebugDrawBase();
}
