#include "GameOverObserver.h"
#include "World/Character/Player.h"

namespace Observer
{
	GameOverObserver::GameOverObserver(Player* player) :
		mPlayer(player)
	{
	}

	void GameOverObserver::OnNotify(Event event)
	{
		if (event != Event::PlayerDead) return;

		mPlayer->SetActive(false);
	}
}
