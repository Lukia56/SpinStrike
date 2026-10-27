#pragma once

#include "../Core/Screen.h"

class Player;

namespace UI
{
    class BoxObject;

    class InGameScreen : public Screen
    {
    public:

        InGameScreen(Player* player);
        ~InGameScreen() = default;

        void Init() override;

        void Update() override;

    private:

        BoxObject* mHPBar;
        BoxObject* mMaxHPBar;

        Player* mPlayer;
    };
}
