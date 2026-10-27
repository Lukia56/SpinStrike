#include "TitleMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"

namespace
{
	const char* const kFontPath = "Resources\\Font\\NicoKaku.dft";

	const char* const kStartText = "ゲーム開始";
	constexpr Vector3 kStartButtonPos{ 0.0f, 160.0f, 0.0f };

	const char* const kOptionText = "設定";
	constexpr Vector3 kOptionButtonPos{ 0.0f, 240.0f, 0.0f };

	const char* const kExitText = "ゲーム終了";
	constexpr Vector3 kExitButtonPos{ 0.0f, 320.0f, 0.0f };
}

namespace UI
{
	TitleMenuScreen::TitleMenuScreen()
	{
		UI::UIRoot* itemRoot = GetMenuItemRoot();

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		// 開始ボタン
		MenuItem* startButton = itemRoot->CreateToChild<UI::MenuItem>();
		{
			startButton->GetRectTransform()->localPosition = kStartButtonPos;

			UI::TextObject* text = startButton->CreateToChild<UI::TextObject>(font, kStartText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
			text->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			startButton->SetSelectCallback([text]() { text->SetColor(Color::cyan); });
			startButton->SetDeselectCallback([text]() { text->SetColor(Color::white); });
			startButton->SetSubmitCallback([this]()
				{
					this->SetCommand(UI::Command::StartGame);
					return true;
				});
		}

		// 設定ボタン
		MenuItem* optionButton = itemRoot->CreateToChild<UI::MenuItem>();
		{
			optionButton->GetRectTransform()->localPosition = kOptionButtonPos;

			UI::TextObject* text = optionButton->CreateToChild<UI::TextObject>(font, kOptionText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
			text->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			optionButton->SetSelectCallback([text]() { text->SetColor(Color::cyan); });
			optionButton->SetDeselectCallback([text]() { text->SetColor(Color::white); });
		}

		// 終了ボタン
		MenuItem* exitButton = itemRoot->CreateToChild<UI::MenuItem>();
		{
			exitButton->GetRectTransform()->localPosition = kExitButtonPos;

			UI::TextObject* text = exitButton->CreateToChild<UI::TextObject>(font, kExitText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
			text->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			exitButton->SetSelectCallback([text]() { text->SetColor(Color::cyan); });
			exitButton->SetDeselectCallback([text]() { text->SetColor(Color::white); });
			exitButton->SetSubmitCallback([this]()
				{
					this->SetCommand(UI::Command::QuitGame);
					return true;
				});
		}

		AddMenuItem(startButton);
		AddMenuItem(optionButton);
		AddMenuItem(exitButton);
	}

	void TitleMenuScreen::Init()
	{
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
}
