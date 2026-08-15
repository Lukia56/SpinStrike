#include "UIMenuScreen.h"
#include "UIMenuItem.h"
#include "../Other/RootObject.h"

namespace UI
{
	MenuScreen::MenuScreen() :
		mCursorPos(-1),
		mMenuItemRoot(nullptr)
	{
		mMenuItemRoot = CreateToChild<RootObject>();
	}

	void MenuScreen::Setup()
	{
		mCursorPos = 0;
	}

	void MenuScreen::MoveCursorNext()
	{
		if (mMenuItems.empty()) return;

		mCursorPos++;
		mCursorPos = Math::Clamp(mCursorPos, 0, static_cast<int>(mMenuItems.size()) - 1);
	}

	void MenuScreen::MoveCursorPrev()
	{
		if (mMenuItems.empty()) return;

		mCursorPos--;
		mCursorPos = Math::Clamp(mCursorPos, 0, static_cast<int>(mMenuItems.size()) - 1);
	}

	void MenuScreen::InvokeSubmit()
	{
		if (mMenuItems.empty()) return;

		mMenuItems[mCursorPos]->InvokeSubmit();
	}

	void MenuScreen::InvokeCancel()
	{
		if (mMenuItems.empty()) return;

		mMenuItems[mCursorPos]->InvokeCancel();
	}

	void MenuScreen::AddMenuItem(MenuItem* menuItem)
	{
		mMenuItems.emplace_back(menuItem);
	}
} 
