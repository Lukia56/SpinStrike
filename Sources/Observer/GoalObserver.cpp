#include "GoalObserver.h"
#include "World/Character/Player.h"

namespace Observer
{
	GoalObserver::GoalObserver(Player* player) :
		mPlayer(player)
	{
	}

	void GoalObserver::OnNotify(Event event)
	{
		if (event != Event::PlayerGoal) return;

		mPlayer->SetActive(false);
	}
}
