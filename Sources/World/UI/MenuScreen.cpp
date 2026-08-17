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
		SetCursorPos(0);
	}

	void MenuScreen::MoveCursorNext()
	{
		if (mMenuItems.empty()) return;

		SetCursorPos(mCursorPos + 1);
	}

	void MenuScreen::MoveCursorPrev()
	{
		if (mMenuItems.empty()) return;

		SetCursorPos(mCursorPos - 1);
	}

	bool MenuScreen::InvokeSubmit()
	{
		if (mMenuItems.size() <= mCursorPos) return true;

		return mMenuItems[mCursorPos]->InvokeSubmit();
	}

	bool MenuScreen::InvokeCancel()
	{
		if (mMenuItems.size() <= mCursorPos) return true;

		return mMenuItems[mCursorPos]->InvokeCancel();
	}

	void MenuScreen::AddMenuItem(MenuItem* menuItem)
	{
		mMenuItems.emplace_back(menuItem);
	}

	void MenuScreen::SetCursorPos(int nextPos)
	{
		int prevPos = mCursorPos;

		mCursorPos = nextPos;
		mCursorPos = Math::Clamp(mCursorPos, 0, static_cast<int>(mMenuItems.size()) - 1);

		if (mCursorPos == prevPos) return;

		if (mMenuItems.size() > prevPos) mMenuItems[prevPos]->InvokeDeselect();
		if (mMenuItems.size() > mCursorPos) mMenuItems[mCursorPos]->InvokeSelect();
	}
} 
