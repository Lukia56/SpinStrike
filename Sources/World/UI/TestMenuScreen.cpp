#include "TestMenuScreen.h"
#include <DxLib.h>
#include "MenuItem.h"
#include "TextObject.h"
#include "System/Input/Literal/InputState.h"
#include "UIRoot.h"

namespace
{
	const char* const kFontPath = "Resources\\Font\\JFDotK12.dft";

	const char* const kStartText = "Start";
	const char* const kOptionText = "Option";
	const char* const kExitText = "Exit";
}

UI::TestMenuScreen::TestMenuScreen()
{
}

void UI::TestMenuScreen::Init()
{
	UI::UIRoot* itemRoot = GetMenuItemRoot();
	auto startItem = itemRoot->CreateToChild<MenuItem>([&]()
		{
			return true;
		});
	startItem->GetRectTransform()->localPosition.y = 0.0f;
	startItem->CreateToChild<TextObject>(kFontPath, kStartText);

	auto optionItem = itemRoot->CreateToChild<MenuItem>([]()
		{
			DrawBox(0, 0, 960, 540, 0xffffff, 1);
			return true;
		});
	optionItem->GetRectTransform()->localPosition.y = 100.0f;
	optionItem->CreateToChild<TextObject>(kFontPath, kOptionText);

	auto exitItem = itemRoot->CreateToChild<MenuItem>(
		[this]()
		{
			SetCommand(Command::ExitTestScene);
			return true;
		});
	exitItem->GetRectTransform()->localPosition.y = 200.0f;
	exitItem->CreateToChild<TextObject>(kFontPath, kExitText);

	AddMenuItem(startItem);
	AddMenuItem(optionItem);
	AddMenuItem(exitItem);
}

void UI::TestMenuScreen::Update()
{
}

void UI::TestMenuScreen::Setup()
{
	MenuScreen::Setup();
}

bool UI::TestMenuScreen::ProcessInput(const Input::UIInputState& input)
{
	if (input.up)
	{
		MoveCursorPrev();
	}
	if (input.down)
	{
		MoveCursorNext();
	}
	if (input.submit)
	{
		if (!InvokeSubmit()) return false;
	}

	return true;
}
