#pragma once

#include "IObserver.h"

class Player;

namespace Observer
{
	class GameOverObserver : public IObserver
	{
	public:

		GameOverObserver(Player* player);
		~GameOverObserver() = default;

		void OnNotify(Event event) override;

	private:

		Player* mPlayer;
	};
}
