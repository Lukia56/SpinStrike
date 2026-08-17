#include "TestMenuScreen.h"
#include <DxLib.h>
#include "ImageObject.h"
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

namespace UI
{
	TestMenuScreen::TestMenuScreen()
	{
	}

	void TestMenuScreen::Init()
	{
		UI::UIRoot* itemRoot = GetMenuItemRoot();

		// 開始ボタン
		auto startItem = itemRoot->CreateToChild<MenuItem>();
		startItem->GetRectTransform()->localPosition.y = 0.0f;
		TextObject* startText = startItem->CreateToChild<TextObject>(kFontPath, kStartText);
		
		startItem->SetSelectCallback([startText]() { startText->SetColor(Color::yellow); });
		startItem->SetDeselectCallback([startText]() { startText->SetColor(Color::white); });

		// 設定ボタン
		auto optionItem = itemRoot->CreateToChild<MenuItem>();
		optionItem->GetRectTransform()->localPosition.y = 100.0f;
		TextObject* optionText = optionItem->CreateToChild<TextObject>(kFontPath, kOptionText);

		optionItem->SetSelectCallback([optionText]() { optionText->SetColor(Color::yellow); });
		optionItem->SetDeselectCallback([optionText]() { optionText->SetColor(Color::white); });

		// 終了ボタン
		auto exitItem = itemRoot->CreateToChild<MenuItem>();
		exitItem->GetRectTransform()->localPosition.y = 200.0f;
		TextObject* exitText = exitItem->CreateToChild<TextObject>(kFontPath, kExitText);

		exitItem->SetSelectCallback([exitText]() { exitText->SetColor(Color::yellow); });
		exitItem->SetDeselectCallback([exitText]() { exitText->SetColor(Color::white); });
		exitItem->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::ExitTestScene);
				return true;
			});

		AddMenuItem(startItem);
		AddMenuItem(optionItem);
		AddMenuItem(exitItem);
	}

	void TestMenuScreen::Update()
	{
	}

	void TestMenuScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool TestMenuScreen::ProcessInput(const Input::UIInputState& input)
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
}
