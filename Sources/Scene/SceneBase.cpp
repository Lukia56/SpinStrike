#include "SceneBase.h"
#include <cassert>
#include <memory>
#include "../World/GameObject.h"
#include "Camera/CameraManager.h"
#include "Camera/CameraStatic.h"
#include "Collision/CollisionManager.h"

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

void SceneBase::Init()
{
	OnInit();
}

void SceneBase::Finalize()
{
	OnFinalize();
}

std::unique_ptr<SceneBase> SceneBase::Update()
{
	UpdateRootObjects();

	// TODO: PostUpdate

	mCameraManager->Update();

	return OnUpdate();
}

void SceneBase::PhysicsUpdate()
{
	PhysicsUpdateRootObjects();

	CollisionManager::GetInstance().CheckAllCollision();
}

void SceneBase::Draw()
{
	mCameraManager->Bind();

	DrawRootObjects();

	OnDraw();
}

void SceneBase::DebugDraw()
{
	DebugDrawRootObjects();

	mCameraManager->DebugDraw();

	OnDebugDraw();
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

void SceneBase::PhysicsUpdateRootObjects()
{
	for (const auto& it : mRootObjects)
	{
		PhysicsUpdateGameObject(it.get());
	}
}

void SceneBase::DrawRootObjects()
{
	for (const auto& it : mRootObjects)
	{
		DrawGameObject(it.get());
	}
}

void SceneBase::DebugDrawRootObjects()
{
	for (const auto& it : mRootObjects)
	{
		DebugDrawGameObject(it.get());
	}
}

void SceneBase::UpdateGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->Update();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform()->GetChildren())
	{
		UpdateGameObject(it.get());
	}
}

void SceneBase::PhysicsUpdateGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->PhysicsUpdate();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform()->GetChildren())
	{
		PhysicsUpdateGameObject(it.get());
	}
}

void SceneBase::DrawGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->Draw();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform()->GetChildren())
	{
		DrawGameObject(it.get());
	}
}

void SceneBase::DebugDrawGameObject(GameObject* gameObject)
{
	if (!gameObject->IsActive()) return;

	gameObject->DebugDraw();

	// 子オブジェクトについて再帰
	for (const auto& it : gameObject->GetTransform()->GetChildren())
	{
		DebugDrawGameObject(it.get());
	}
}
