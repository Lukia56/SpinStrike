#include "Screen.h"
#include <DxLib.h>
#include "../Component/RectTransform.h"

namespace UI
{
	Screen::Screen() :
		mCommand(Command::None)
	{
		int width, height;
		GetWindowSize(&width, &height);

		mRectTransform->SetPivot(Vector2::Zero);
		mRectTransform->SetFullRectAsFixed(Vector2(static_cast<float>(width), static_cast<float>(height)));
	}

	Command Screen::ConsumeCommand()
	{
		Command buf = mCommand;
		mCommand = Command::None;
		return buf;
	}
}
