#include "SceneEffekseerTest.h"
#include <imgui.h>
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "System/Input/Keyboard.h"
#include "World/Object/DebugGround.h"
#include "World/Test/EffectTest.h"

SceneEffekseerTest::SceneEffekseerTest()
{
}

void SceneEffekseerTest::OnInit()
{
	AddToRoot<DebugGround>();

	AddToRoot<EffectTest>();

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
}

std::unique_ptr<SceneBase> SceneEffekseerTest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
