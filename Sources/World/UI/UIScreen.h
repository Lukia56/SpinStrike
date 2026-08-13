#pragma once

#include "UIObject.h"
#include "UICommand.h"

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
		/// コマンドを取得し、初期値へ戻す
		/// </summary>
		Command ConsumeCommand();

	protected:

		void SetCommand(Command command) { mCommand = command; }

	private:

		Command mCommand;
	};
}
