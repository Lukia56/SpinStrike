#include "InGameScreen.h"
#include "../Widget/InGame/PlayerHPUI.h"
#include "../Widget/InGame/PlayerStaminaUI.h"
#include "World/Character/Player.h"

namespace UI
{
	InGameScreen::InGameScreen(Player* player) :
		mPlayer(player)
	{
	}

	void InGameScreen::Init()
	{
		CreateToChild<UI::PlayerHPUI>(mPlayer);
		CreateToChild<UI::PlayerStaminaUI>(mPlayer);
	}

	void InGameScreen::Update()
	{
	}
}
