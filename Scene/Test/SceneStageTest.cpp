#include "SceneStageTest.h"
#include <memory>
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "Stage/StageModelDataBase.h"
#include "Factory/StageObjectCreator.h"
#include "Utility/Data/JSON/JsonLoader.h"
#include "World/Objects/DebugGround.h"

namespace
{
	const char* const kParamPath = "Resource\\MasterData\\TestLevel.json";
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

	auto dataBase = std::make_unique<Stage::StageModelDataBase>();

	auto creator = std::make_unique<StageObjectCreator>(dataBase.get());

	auto params = Data::Json::LoadJsonAs<StageObjectParam>(kParamPath);
	// ステージオブジェクト生成
	for (const auto& param : params)
	{
		creator->SetParam(param);
		AddToRoot(creator->CreateInstance());
	}
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
