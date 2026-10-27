#include "PlayerHPUI.h"
#include "../BoxObject.h"
#include "System/PlayerDataManager.h"
#include "World/Character/Player.h"

namespace
{
	constexpr Vector3 kBarPos{ 200.0f, 75.0f, 0.0f };
	constexpr Vector2 kBarSize{ 400.0f, 75.0f };
	constexpr Vector2 kBarPivot{ 0.0f, 0.0f };
}

namespace UI
{
	PlayerHPUI::PlayerHPUI(Player* player) :
		mHPBar(nullptr),
		mMaxHPBar(nullptr),
		mPlayer(player)
	{
	}

	void PlayerHPUI::Init()
	{
		mRectTransform->SetAnchor(RectTransform::Anchor::FullStretch);

		mMaxHPBar = CreateToChild<UI::BoxObject>(Color::red);
		mMaxHPBar->GetRectTransform()->localPosition = kBarPos;
		mMaxHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);
		mMaxHPBar->GetRectTransform()->SetPivot(kBarPivot);
		mMaxHPBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);

		mHPBar = CreateToChild<UI::BoxObject>(Color::green);
		mHPBar->GetRectTransform()->localPosition = kBarPos;
		mHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);
		mHPBar->GetRectTransform()->SetPivot(kBarPivot);
		mHPBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);
	}

	void PlayerHPUI::Update()
	{
		float hpRate = static_cast<float>(mPlayer->GetHP()) / static_cast<float>(PlayerDataManager::GetInstance().GetPlayerParam().maxHp);
		mHPBar->GetRectTransform()->SetRectWidthAsFixed(kBarSize.x * hpRate);
	}
}
