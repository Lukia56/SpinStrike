#include "SceneCollisionDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "Collision/Collision3D.h"
#include "System/Input/Keyboard.h"
#include "System/InputManager.h"
#include "World/Objects/DebugGround.h"

SceneCollisionDebug::SceneCollisionDebug() :
	mShapeA(nullptr),
	mShapeB(nullptr),
	mIsControllCamera(true)
{
	AddToRoot<DebugGround>();

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);

	mShapeA = std::make_unique<Collision::AABB3D>(Vector3(50, 100, 50));
	mShapeB = std::make_unique<Collision::AABB3D>(Vector3(100, 200, 100));

	mShapeAPos = Vector3(100.0f, 100.0f, 0.0f);
	mShapeBPos = Vector3(-100.0f, 100.0f, 0.0f);
}

void SceneCollisionDebug::Init()
{
}

std::unique_ptr<SceneBase> SceneCollisionDebug::Update()
{
	mShapeA->SetPosition(mShapeAPos);
	mShapeB->SetPosition(mShapeBPos);

	if (!mIsControllCamera)
	{
		mShapeAPos += InputManager::GetInstance().GetAsVector3(Input::Action::Move);
		mShapeAPos.y += InputManager::GetInstance().GetAsFloat(Input::Action::Fly);
	}

	if (InputManager::GetInstance().IsPressed(Input::Action::Submit))
	{
		mIsControllCamera = !mIsControllCamera;

		Camera::Type type = mIsControllCamera ? Camera::Type::DebugFree : Camera::Type::Static;
		
		GetCameraManager()->SetCurrentCameraType(type);
	}

	return nullptr;
}

void SceneCollisionDebug::DebugDraw()
{
	bool isHit = mShapeA->CheckCollision(mShapeB.get()).isHit;
	Color color = isHit ? Color::red : Color::white;

	mShapeA->DebugDraw(color);
	mShapeB->DebugDraw(color);
}
