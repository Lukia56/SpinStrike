#include "SceneLoadStageTest.h"
#include <memory>
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "World/Object/DebugGround.h"
#include "World/Other/StageManager.h"

namespace
{
	const char* const kStageObjectDataPath = "Resources\\MasterData\\TestLevel.json";
}

SceneLoadStageTest::SceneLoadStageTest() :
	mIsStartTransition(false)
{
}

void SceneLoadStageTest::Init()
{
	AddToRoot<DebugGround>();
	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);

	AddToRoot<StageManager>(kStageObjectDataPath);
}

std::unique_ptr<SceneBase> SceneLoadStageTest::Update()
{
	if (mIsStartTransition) return std::make_unique<SceneSelectDebug>();

	return nullptr;
}

void SceneLoadStageTest::DebugDraw()
{
	if (ImGui::Begin("Scene"))
	{
		if (ImGui::Button("Back to Selection"))
		{
			mIsStartTransition = true;
		}

		ImGui::End();
	}
}
