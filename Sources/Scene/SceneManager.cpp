#include "SceneManager.h"
#include <memory>
#include "SceneBase.h"
#include "SceneInit.h"
#include "Camera/CameraManager.h"

SceneManager::SceneManager() :
	mIsSceneTransitioned(false),
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

bool SceneManager::Update()
{
	mIsSceneTransitioned = false;

	auto nextScene = mCurrentScene->Update();

	if (mCurrentScene->IsQuitApp()) return false;
	if (nextScene == nullptr) return true;

	// シーンを切り替える
	nextScene->Init();
	mCurrentScene->Finalize();
	mCurrentScene = std::move(nextScene);

	mIsSceneTransitioned = true;

	return true;
}

void SceneManager::PhysicsUpdate()
{
	if (mIsSceneTransitioned) return;

	mCurrentScene->PhysicsUpdate();
}

void SceneManager::Draw()
{
	if (mIsSceneTransitioned) return;

	mCurrentScene->Draw();
}

void SceneManager::DebugDraw()
{
	if (mIsSceneTransitioned) return;

	mCurrentScene->DebugDraw();
}
