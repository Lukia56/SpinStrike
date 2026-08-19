#include "SceneTitle.h"
#include "System/InputManager.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/TitleMenuScreen.h"

SceneTitle::SceneTitle() :
	mUIManager(nullptr)
{
}

void SceneTitle::OnInit()
{
	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<TitleMenuScreen>());

	mUIManager->PushScreen<TitleMenuScreen>();
}

std::unique_ptr<SceneBase> SceneTitle::OnUpdate()
{
	mUIManager->ProcessInput(InputManager::GetInstance().GetUIInputState());

	UI::Command command = mUIManager->ConsumeCommand();
	switch (command)
	{
	case UI::Command::OpenOptions:
		//mUIManager->PushScreen<OptionScreen>();
		break;
	}

	return nullptr;
}
