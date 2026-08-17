#include "TestOptionScreen.h"
#include <DxLib.h>
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/Input/Literal/InputState.h"

namespace
{
	const char* const kFontPath = "Resources\\Font\\JFDotK12.dft";

	const char* const kBGMVolumeText = "BGM Volume: 50%";
	const char* const kSEVolumeText = "SE Volume: 50%";
}

namespace UI
{
	TestOptionScreen::TestOptionScreen()
	{
	}

	void TestOptionScreen::Init()
	{
		UI::UIRoot* itemRoot = GetMenuItemRoot();

		// BGMボタン
		auto bgmItem = itemRoot->CreateToChild<MenuItem>();
		bgmItem->GetRectTransform()->localPosition.y = 50.0f;
		bgmItem->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));
		TextObject* bgmText = bgmItem->CreateToChild<TextObject>(kFontPath, kBGMVolumeText);
		bgmText->SetHolizontalAlignment(HolizontalAlignment::Center);
		bgmText->SetVerticalAlignment(VerticalAlignment::Middle);
		bgmText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		bgmItem->SetSelectCallback([bgmText]() { bgmText->SetColor(Color::yellow); });
		bgmItem->SetDeselectCallback([bgmText]() { bgmText->SetColor(Color::white); });
		bgmItem->SetCancelCallback([]() { return false; });

		// SEボタン
		auto seItem = itemRoot->CreateToChild<MenuItem>();
		seItem->GetRectTransform()->localPosition.y = 150.0f;
		seItem->GetRectTransform()->SetFullRectAsFixed(Vector2(160.0f, 32.0f));
		TextObject* seText = seItem->CreateToChild<TextObject>(kFontPath, kSEVolumeText);
		seText->SetHolizontalAlignment(HolizontalAlignment::Center);
		seText->SetVerticalAlignment(VerticalAlignment::Middle);
		seText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		seItem->SetSelectCallback([seText]() { seText->SetColor(Color::yellow); });
		seItem->SetDeselectCallback([seText]() { seText->SetColor(Color::white); });
		seItem->SetCancelCallback([]() { return false; });

		AddMenuItem(bgmItem);
		AddMenuItem(seItem);
	}

	void TestOptionScreen::Update()
	{
	}

	void TestOptionScreen::Draw()
	{
		Rect rect = GetRectTransform()->CalculateRect();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
		DrawBox(rect.xMin, rect.yMin, rect.xMin + rect.width, rect.yMin + rect.height, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	void TestOptionScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool TestOptionScreen::ProcessInput(const Input::UIInputState& input)
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
