#include "PlayerStaminaUI.h"
#include "../BoxObject.h"
#include "System/PlayerDataManager.h"
#include "System/TimeManager.h"
#include "World/Character/Player.h"

namespace
{
	constexpr Vector3 kBarPos{ 150.0f, 120.0f, 0.0f };
	constexpr Vector2 kBarSize{ 25.0f, 200.0f };
	constexpr Vector2 kBarPivot{ 0.0f, 1.0f };

	constexpr float kFadeSpeed = 2.0f;
}

namespace UI
{
	PlayerStaminaUI::PlayerStaminaUI(Player* player) :
		mAlpha(0.0f),
		mStaminaBar(nullptr),
		mMaxStaminaBar(nullptr),
		mPlayer(player)
	{
	}

	void PlayerStaminaUI::Init()
	{
		mRectTransform->SetAnchor(RectTransform::Anchor::FullStretch);

		mMaxStaminaBar = CreateToChild<UI::BoxObject>(Color::red);
		mMaxStaminaBar->GetRectTransform()->localPosition = kBarPos;
		mMaxStaminaBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterMiddle);
		mMaxStaminaBar->GetRectTransform()->SetPivot(kBarPivot);
		mMaxStaminaBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);

		mStaminaBar = CreateToChild<UI::BoxObject>(Color::yellow);
		mStaminaBar->GetRectTransform()->localPosition = kBarPos;
		mStaminaBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterMiddle);
		mStaminaBar->GetRectTransform()->SetPivot(kBarPivot);
		mStaminaBar->GetRectTransform()->SetFullRectAsFixed(kBarSize);
	}

	void PlayerStaminaUI::Update()
	{
		if (mAlpha > 0.0f)
		{
			mAlpha -= kFadeSpeed * TimeManager::GetDeltaTime();
		}

		// スタミナ量反映
		if (mPlayer->IsSpinning())
		{
			float staminaRate = mPlayer->GetSpinStamina() / PlayerDataManager::GetInstance().GetPlayerParam().spinStaminaDuration;
			mStaminaBar->GetRectTransform()->SetRectHeightAsFixed(kBarSize.y * staminaRate);
			mAlpha = 1.0f;
		}

		// バーのアルファ値設定
		Color color;

		color = mStaminaBar->GetColor();
		color.a = mAlpha;
		mStaminaBar->SetColor(color);

		color = mMaxStaminaBar->GetColor();
		color.a = mAlpha;
		mMaxStaminaBar->SetColor(color);
	}
}
