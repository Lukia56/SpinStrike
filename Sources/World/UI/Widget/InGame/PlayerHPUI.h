#pragma once

#include "World/UI/Core/UIObject.h"

class Player;

namespace UI
{
	class BoxObject;

	class PlayerHPUI : public UIObject
	{
	public:

		PlayerHPUI(Player* player);
		~PlayerHPUI() = default;

		void Init() override;
		void Update() override;

	private:

		BoxObject* mHPBar;
		BoxObject* mMaxHPBar;

		Player* mPlayer;
	};
}
