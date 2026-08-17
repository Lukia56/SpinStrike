#include "UIManager.h"
#include <stack>
#include <typeindex>
#include <unordered_map>
#include "Command.h"
#include "Screen.h"
#include "System/Input/Literal/InputState.h"

namespace UI
{
	UIManager::UIManager() :
		mActiveScreenRoot(nullptr),
		mPoolScreenRoot(nullptr)
	{
		mActiveScreenRoot = CreateToChild<RootObject>();
		mPoolScreenRoot = CreateToChild<RootObject>();
		mPoolScreenRoot->SetActive(false);
	}

	void UIManager::ProcessInput(const Input::UIInputState& input)
	{
		if (mActiveScreens.empty()) return;

		if (!mActiveScreens.top()->ProcessInput(input)) PopScreen();
	}

	void UIManager::PopScreen()
	{
		if (mActiveScreens.empty()) return;

		Screen* screen = mActiveScreens.top();
		mActiveScreens.pop();

		screen->GetTransform()->ChangeParent(mPoolScreenRoot->GetTransform());
		mPoolScreen.insert_or_assign(typeid(*screen), screen);
	}

	Command UIManager::ConsumeCommand()
	{
		if (mActiveScreens.empty()) return Command::None;

		return mActiveScreens.top()->ConsumeCommand();
	}
}