#include "SceneUITest.h"
#include <DxLib.h>
#include "SceneSelectDebug.h"
#include "System/Input/Keyboard.h"
#include "World/UI/UIImage.h"

namespace
{
	const char* const kSpritePath = "Resources\\Sprites\\Grass.png";
}

SceneUITest::SceneUITest()
{
}

void SceneUITest::OnInit()
{
	auto image = CreateToRoot<UIImage>(kSpritePath);
	image->GetTransform().Translate(500, 500, 0);
}

std::unique_ptr<SceneBase> SceneUITest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
