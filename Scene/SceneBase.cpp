#include "SceneBase.h"
#include <cassert>
#include <memory>
#include "../World/GameObject.h"
#include "Camera/CameraManager.h"
#include "Camera/CameraStatic.h"

SceneBase::SceneBase() :
	mCameraManager(nullptr)
{
	mCameraManager = std::make_unique<CameraManager>();
	mCameraManager->AddCamera(Camera::Type::Static, std::make_unique<CameraStatic>());
	mCameraManager->SetCurrentCameraType(Camera::Type::Static);
}

SceneBase::~SceneBase()
{
	mCameraManager.reset();

	while (mRootObjects.size() > 0)
	{
		auto it = mRootObjects.begin();
		(*it)->Finalize();
		mRootObjects.erase(it);
	}
}

std::unique_ptr<SceneBase> SceneBase::UpdateBase()
{
	UpdateRootObjects();

	mCameraManager->Update();

	return Update();
}

void SceneBase::DrawBase()
{
	mCameraManager->Bind();

	DrawRootObjects();

	mCameraManager->DebugDraw();
}

void SceneBase::UpdateRootObjects()
{
	for (const auto& it : mRootObjects)
	{
		UpdateGameObject(it.get());
	}

	// 削除チェック
	for (const auto& it : mRootObjects)
	{
		it->CheckDestroy();
	}
}

void SceneBase::DrawRootObjects()
{
	for (const auto& it : mRootObjects)
	{
		DrawGameObject(it.get());
	}
}

void SceneBase::UpdateGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->Update();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform().GetChildren())
	{
		UpdateGameObject(it.get());
	}
}

void SceneBase::DrawGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->Draw();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform().GetChildren())
	{
		DrawGameObject(it.get());
	}
}
