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
#include "Stage/StageLoader.h"

namespace
{
	const char* const kStageDataPath = "Resource\\MasterData\\TestLevel.json";
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

	GameObjectContainer objects = Stage::StageLoader::Load(kStageDataPath);

	for (auto& object : objects)
	{
		AddToRoot(std::move(object));
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
