#include "SceneMenuUITest.h"
#include "SceneSelectDebug.h"
#include "System/InputManager.h"
#include "System/Input/Keyboard.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Test/TestMenuScreen.h"
#include "World/UI/Test/TestOptionScreen.h"

SceneMenuUITest::SceneMenuUITest() :
	mUIManager(nullptr)
{
}

void SceneMenuUITest::OnInit()
{
	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::TestMenuScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::TestOptionScreen>());

	mUIManager->PushScreen<UI::TestMenuScreen>();
}

std::unique_ptr<SceneBase> SceneMenuUITest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Y))
	{
		mUIManager->PushScreen<UI::TestMenuScreen>();
	}
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_T))
	{
		mUIManager->PopScreen();
	}

	mUIManager->ProcessInput(InputManager::GetInstance().GetUIInputState());

	UI::Command command = mUIManager->ConsumeCommand();
	if (command == UI::Command::ExitTestScene)
	{
		return std::make_unique<SceneSelectDebug>();
	}
	else
	if (command == UI::Command::OpenOptions)
	{
		mUIManager->PushScreen<UI::TestOptionScreen>();
	}

	return nullptr;
}
