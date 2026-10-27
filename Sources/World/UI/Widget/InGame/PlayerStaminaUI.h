#pragma once

#include "World/UI/Core/UIObject.h"

class Player;

namespace UI
{
	class BoxObject;

	class PlayerStaminaUI : public UIObject
	{
	public:

		PlayerStaminaUI(Player* player);
		~PlayerStaminaUI() = default;

		void Init() override;
		void Update() override;

	private:

		float mAlpha;

		BoxObject* mStaminaBar;
		BoxObject* mMaxStaminaBar;

		Player* mPlayer;
	};
}
