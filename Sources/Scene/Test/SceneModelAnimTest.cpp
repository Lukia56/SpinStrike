#include "SceneModelAnimTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "System/ResourceManager.h"
#include "System/Input/Keyboard.h"
#include "System/Resource/Model.h"
#include "World/Test/ModelTest.h"

namespace
{
	const char* const kModelPath1 = "Resources\\Model\\Mage.mv1";
	const char* const kModelPath2 = "Resources\\Model\\Rogue_Hooded.mv1";
	const char* const kAnimModelPath = "Resources\\Model\\Rig_Medium_MovementBasic.mv1";
}

SceneModelAnimTest::SceneModelAnimTest()
{
}

void SceneModelAnimTest::OnInit()
{
	auto model1 = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath1);
	auto model2 = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath2);
	auto anim = ResourceManager::GetInstance().GetResource<Resource::Model>(kAnimModelPath);

	auto obj1 = CreateToRoot<ModelTest>(model1, anim, 6);
	obj1->GetTransform()->Translate(250, 0, 0);
	obj1->GetTransform()->localScale *= 100.0f;
	auto obj2 = CreateToRoot<ModelTest>(model2, anim, 3);
	obj2->GetTransform()->Translate(-250, 0, 0);
	obj2->GetTransform()->localScale *= 100.0f;

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
}

std::unique_ptr<SceneBase> SceneModelAnimTest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
