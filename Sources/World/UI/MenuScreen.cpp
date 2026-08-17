#include "MenuScreen.h"
#include "MenuItem.h"
#include "UIRoot.h"

namespace UI
{
	MenuScreen::MenuScreen() :
		mCursorPos(-1),
		mMenuItemRoot(nullptr)
	{
		mMenuItemRoot = CreateToChild<UIRoot>();
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

	bool MenuScreen::InvokeSubmit()
	{
		if (mMenuItems.empty()) return true;

		return mMenuItems[mCursorPos]->InvokeSubmit();
	}

	bool MenuScreen::InvokeCancel()
	{
		if (mMenuItems.empty()) return true;

		return mMenuItems[mCursorPos]->InvokeCancel();
	}

	void MenuScreen::AddMenuItem(MenuItem* menuItem)
	{
		mMenuItems.emplace_back(menuItem);
	}
} 
