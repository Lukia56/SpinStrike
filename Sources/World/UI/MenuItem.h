#pragma once

#include "UIObject.h"
#include <functional>

namespace UI
{
	/// <summary>
	/// メニューの一項目
	/// </summary>
	class MenuItem : public UIObject
	{
	public:

		MenuItem(const std::function<bool(void)>& onSubmit, const std::function<bool(void)>& onCancel);
		~MenuItem() = default;

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

	private:

		std::function<bool(void)> mOnSubmit;

		std::function<bool(void)> mOnCancel;
	};
}
