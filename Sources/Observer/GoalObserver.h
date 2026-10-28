#pragma once

#include "IObserver.h"

class Player;

namespace Observer
{
	class GoalObserver : public IObserver
	{
	public:

		GoalObserver(Player* player);
		~GoalObserver() = default;

		void OnNotify(Event event) override;

	private:

		Player* mPlayer;
	};
}
