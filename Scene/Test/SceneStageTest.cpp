#include "SceneStageTest.h"
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Objects/StageObject.h"
#include "World/Objects/DebugGround.h"

namespace
{
	const char* const kParamPath = "Resource\\MasterData\\TestLevel.json";
}

SceneStageTest::SceneStageTest() :
	mStageObject(nullptr),
	mIsStartTransition(false)
{
	AddToRoot<DebugGround>();
	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
}

void SceneStageTest::Init()
{
	auto param = Data::Json::LoadJsonAs<StageObjectParam>(kParamPath);
	for (const auto& p : param)
	{
		AddToRoot<StageObject>(p);
	}

	//mStageObject = AddToRoot<StageObject>(param[0]);
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
