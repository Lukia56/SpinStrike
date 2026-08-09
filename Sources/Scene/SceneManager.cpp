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
	auto nextScene = mCurrentScene->Update();
	if (nextScene == nullptr) return;

	// シーンを切り替える
	nextScene->Init();
	mCurrentScene->Finalize();
	mCurrentScene = std::move(nextScene);
}

void SceneManager::PhysicsUpdate()
{
	mCurrentScene->PhysicsUpdate();
}

void SceneManager::Draw()
{
	mCurrentScene->Draw();
}

void SceneManager::DebugDraw()
{
	mCurrentScene->DebugDraw();
}
