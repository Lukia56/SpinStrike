#pragma once

#include "UIObject.h"
#include "Command.h"

namespace Input
{
	struct UIInputState;
}

namespace UI
{
	/// <summary>
	/// UIの一画面の基底
	/// UIオブジェクトを管理する
	/// </summary>
	class Screen : public UIObject
	{
	public:

		Screen();
		virtual ~Screen() = default;

		/// <summary>
		/// 使用前準備処理
		/// </summary>
		virtual void Setup() {};

		/// <summary>
		/// 入力処理
		/// </summary>
		/// <returns>画面を閉じるならfalseを返す</returns>
		virtual bool ProcessInput(const Input::UIInputState& input) { return true; }

		/// <summary>
		/// コマンドを取得し、初期値へ戻す
		/// </summary>
		Command ConsumeCommand();

	protected:

		void SetCommand(Command command) { mCommand = command; }

	private:

		Command mCommand;
	};
}
