#include "TitleMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/Input/Literal/InputState.h"

namespace
{
	const char* const kFontPath = "Resources\\Font\\NicoKaku.dft";

	const char* const kStartText = "ゲーム開始";
	const char* const kOptionText = "設定";
}

TitleMenuScreen::TitleMenuScreen()
{
}

void TitleMenuScreen::Init()
{
	UI::UIRoot* itemRoot = GetMenuItemRoot();

	// 開始ボタン
	auto startButton = itemRoot->CreateToChild<UI::MenuItem>();
	startButton->GetRectTransform()->localPosition.y = 160.0f;
	startButton->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));

	UI::TextObject* startText = startButton->CreateToChild<UI::TextObject>(kFontPath, kStartText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
	startText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);
	
	startButton->SetSelectCallback([startText]() { startText->SetColor(Color::cyan); });
	startButton->SetDeselectCallback([startText]() { startText->SetColor(Color::white); });

	// 設定ボタン
	auto optionButton = itemRoot->CreateToChild<UI::MenuItem>();
	optionButton->GetRectTransform()->localPosition.y = 240.0f;
	optionButton->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));

	UI::TextObject* optionText = optionButton->CreateToChild<UI::TextObject>(kFontPath, kOptionText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
	optionText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

	optionButton->SetSelectCallback([optionText]() { optionText->SetColor(Color::cyan); });
	optionButton->SetDeselectCallback([optionText]() { optionText->SetColor(Color::white); });
	optionButton->SetSubmitCallback([this]()
		{
			this->SetCommand(UI::Command::OpenOptions);
			return true;
		});

	AddMenuItem(startButton);
	AddMenuItem(optionButton);
}

void TitleMenuScreen::Update()
{
}

void TitleMenuScreen::Setup()
{
	MenuScreen::Setup();
}

bool TitleMenuScreen::ProcessInput(const Input::UIInputState& input)
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
