#include "SceneMenuUITest.h"
#include "SceneSelectDebug.h"
#include "System/InputManager.h"
#include "System/Input/Keyboard.h"
#include "World/UI/TestMenuScreen.h"

SceneMenuUITest::SceneMenuUITest() :
	mScreen(nullptr)
{
}

void SceneMenuUITest::OnInit()
{
	mScreen = CreateToRoot<UI::TestMenuScreen>();
	mScreen->Setup();
}

std::unique_ptr<SceneBase> SceneMenuUITest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	mScreen->ProcessInput(InputManager::GetInstance().GetUIInputState());

	UI::Command command = mScreen->ConsumeCommand();
	if (command == UI::Command::ExitTestScene)
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
