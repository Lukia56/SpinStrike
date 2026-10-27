#include "PlayerHPUI.h"
#include "../BoxObject.h"
#include "System/PlayerDataManager.h"
#include "World/Character/Player.h"

namespace
{
	constexpr Vector3 kBarPos{ 200.0f, -75.0f, 0.0f };
	constexpr Vector2 kBarSize{ 300.0f, 50.0f };
	constexpr Vector2 kBarPivot{ 0.0f, 1.0f };

	constexpr Color kBarColor{ 0.239f, 0.87f, 0.09f };
	constexpr Color kMaxBarColor{ 0.3f, 0.3f, 0.3f };
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

		mMaxHPBar = CreateToChild<UI::BoxObject>(kMaxBarColor);
		mMaxHPBar->GetRectTransform()->localPosition = kBarPos;
		mMaxHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftBottom);
		mMaxHPBar->GetRectTransform()->SetPivot(kBarPivot);
		mMaxHPBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);

		mHPBar = CreateToChild<UI::BoxObject>(kBarColor);
		mHPBar->GetRectTransform()->localPosition = kBarPos;
		mHPBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftBottom);
		mHPBar->GetRectTransform()->SetPivot(kBarPivot);
		mHPBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);
	}

	void PlayerHPUI::Update()
	{
		float hpRate = static_cast<float>(mPlayer->GetHP()) / static_cast<float>(PlayerDataManager::GetInstance().GetPlayerParam().maxHp);
		mHPBar->GetRectTransform()->SetRectWidthAsFixed(kBarSize.x * hpRate);
	}
}
