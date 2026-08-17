#include "SceneUITest.h"
#include <DxLib.h>
#include "SceneSelectDebug.h"
#include "System/Input/Keyboard.h"
#include "World/UI/Test/TestScreen.h"

SceneUITest::SceneUITest()
{
}

void SceneUITest::OnInit()
{
	auto screen = CreateToRoot<UI::TestScreen>();
}

std::unique_ptr<SceneBase> SceneUITest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
