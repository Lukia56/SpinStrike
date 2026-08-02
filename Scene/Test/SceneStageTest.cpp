#include "SceneStageTest.h"
#include <memory>
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "World/Objects/DebugGround.h"
#include "World/Others/StageManager.h"

namespace
{
	const char* const kStageObjectDataPath = "Resource\\MasterData\\TestLevel.json";
}

SceneStageTest::SceneStageTest() :
	mIsStartTransition(false)
{
}

void SceneStageTest::Init()
{
	AddToRoot<DebugGround>();
	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);

	AddToRoot<StageManager>(kStageObjectDataPath);
}

std::unique_ptr<SceneBase> SceneStageTest::Update()
{
	if (mIsStartTransition) return std::make_unique<SceneSelectDebug>();

	return nullptr;
}

void SceneStageTest::DebugDraw()
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
