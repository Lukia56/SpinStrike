#include "InGameScreen.h"
#include "../Widget/BoxObject.h"
#include "World/Character/Player.h"

namespace
{
	constexpr Vector3 kHPBarPos{ 200.0f, 75.0f, 0.0f };
	constexpr Vector2 kHPBarSize{ 400.0f, 75.0f };
	constexpr Vector2 kHPBarPivot{ 0.0f, 0.0f };
}

namespace UI
{
	InGameScreen::InGameScreen(Player* player) :
		mHPBar(nullptr),
		mMaxHPBar(nullptr),
		mPlayer(player)
	{
	}

	void InGameScreen::Init()
	{
		BoxObject* maxHPBar = CreateToChild<UI::BoxObject>(Color::red);
		maxHPBar->GetRectTransform()->localPosition = kHPBarPos;
		maxHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);
		maxHPBar->GetRectTransform()->SetPivot(kHPBarPivot);
		maxHPBar->GetRectTransform()->SetFullRectAsFixed(kHPBarSize);

		mHPBar = CreateToChild<UI::BoxObject>(Color::green);
		mHPBar->GetRectTransform()->localPosition = kHPBarPos;
		mHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);
		mHPBar->GetRectTransform()->SetPivot(kHPBarPivot);
		mHPBar->GetRectTransform()->SetFullRectAsFixed(kHPBarSize);
	}

	void InGameScreen::Update()
	{
		float hpRate = static_cast<float>(mPlayer->GetHP()) / static_cast<float>(mPlayer->GetMaxHP());
		mHPBar->GetRectTransform()->SetRectWidthAsFixed(kHPBarSize.x * hpRate);
	}
}
