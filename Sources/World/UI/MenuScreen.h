#pragma once

#include "Screen.h"

class RootObject;

namespace UI
{
	class MenuItem;

	/// <summary>
	/// 操作可能なメニュー画面
	/// </summary>
	class MenuScreen: public Screen
	{
	public:

		MenuScreen();
		virtual ~MenuScreen() = default;

		/// <summary>
		/// 使用前準備処理
		/// 基底ではカーソル位置をリセットする
		/// <para>プールから取得された際に呼ぶ</para>
		/// </summary>
		virtual void Setup();

	protected:

		void MoveCursorNext();
		void MoveCursorPrev();

		/// <summary>
		/// 決定時のコールバックを呼び出す
		/// </summary>
		/// <returns>画面を閉じるならfalseを返す</returns>
		bool InvokeSubmit();

		/// <summary>
		/// キャンセル時のコールバックを呼び出す
		/// </summary>
		/// <returns>画面を閉じるならfalseを返す</returns>
		bool InvokeCancel();

		void AddMenuItem(MenuItem* menuItem);

	protected:

		RootObject* GetMenuItemRoot() const { return mMenuItemRoot; }

	private:

		int mCursorPos;
		
		RootObject* mMenuItemRoot;

		std::vector<MenuItem*> mMenuItems;
	};
}
