#include "SceneCollisionTest.h"
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "Collision/Collision3D.h"
#include "System/Input/Keyboard.h"
#include "System/InputManager.h"
#include "World/Object/DebugGround.h"

SceneCollisionTest::SceneCollisionTest() :
	mShapeA(nullptr),
	mShapeB(nullptr),
	mIsControllCamera(true),
	mIsStartTransition(false)
{
	AddToRoot<DebugGround>();

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);

	mShapeA = std::make_unique<Collision::Capsule3D>(Vector3(0, 50, 0), Vector3(0, -50, 0), 50.0f);
	mShapeB = std::make_unique<Collision::Sphere3D>(50.0f);

	mShapeAPos = Vector3(100.0f, 100.0f, 0.0f);
	mShapeBPos = Vector3(-100.0f, 100.0f, 0.0f);
	mShapeA->SetPosition(mShapeAPos);
	mShapeB->SetPosition(mShapeBPos);
}

void SceneCollisionTest::OnInit()
{
}

std::unique_ptr<SceneBase> SceneCollisionTest::OnUpdate()
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

	if (mIsStartTransition) return std::make_unique<SceneSelectDebug>();

	return nullptr;
}

void SceneCollisionTest::OnDebugDraw()
{
	Collision::Result result = mShapeA->CheckCollision(mShapeB.get());
	Color color = result.isHit ? Color::red : Color::white;
	mShapeA->DebugDraw(color);
	mShapeB->DebugDraw(color);

	if (ImGui::Begin("Scene"))
	{
		if (ImGui::Button("Back to Selection"))
		{
			mIsStartTransition = true;
		}

		ImGui::End();
	}

	if (ImGui::Begin("Collision"))
	{
		float norm[3] = { result.normal.x, result.normal.y, result.normal.z };
		ImGui::InputFloat3("Normal", norm);
		ImGui::Text("Penetration: %.3f", result.penetration);

		ImGui::End();
	}
}
