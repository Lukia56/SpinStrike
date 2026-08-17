#include "TestMenuScreen.h"
#include <DxLib.h>
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/Input/Literal/InputState.h"

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
		startItem->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));
		TextObject* startText = startItem->CreateToChild<TextObject>(kFontPath, kStartText);
		startText->SetHolizontalAlignment(HolizontalAlignment::Center);
		startText->SetVerticalAlignment(VerticalAlignment::Middle);
		startText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);
		
		startItem->SetSelectCallback([startText]() { startText->SetColor(Color::yellow); });
		startItem->SetDeselectCallback([startText]() { startText->SetColor(Color::white); });

		// 設定ボタン
		auto optionItem = itemRoot->CreateToChild<MenuItem>();
		optionItem->GetRectTransform()->localPosition.y = 100.0f;
		optionItem->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));
		TextObject* optionText = optionItem->CreateToChild<TextObject>(kFontPath, kOptionText);
		optionText->SetHolizontalAlignment(HolizontalAlignment::Center);
		optionText->SetVerticalAlignment(VerticalAlignment::Middle);
		optionText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		optionItem->SetSelectCallback([optionText]() { optionText->SetColor(Color::yellow); });
		optionItem->SetDeselectCallback([optionText]() { optionText->SetColor(Color::white); });
		optionItem->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::OpenOptions);
				return true;
			});

		// 終了ボタン
		auto exitItem = itemRoot->CreateToChild<MenuItem>();
		exitItem->GetRectTransform()->localPosition.y = 200.0f;
		exitItem->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));
		TextObject* exitText = exitItem->CreateToChild<TextObject>(kFontPath, kExitText);
		exitText->SetHolizontalAlignment(HolizontalAlignment::Center);
		exitText->SetVerticalAlignment(VerticalAlignment::Middle);
		exitText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

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
		if (input.cancel)
		{
			if (!InvokeCancel()) return false;
		}

		return true;
	}
}
