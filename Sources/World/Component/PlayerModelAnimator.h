#pragma once

#include "ModelAnimator.h"
#include "../Character/PlayerAnimation.h"

class Player;

/// <summary>
/// プレイヤーのアニメーション処理・遷移を行う
/// </summary>
class PlayerModelAnimator :public ModelAnimator
{
public:

	PlayerModelAnimator(Player* player, ModelRenderer* renderer, float fps = TimeManager::kFPS);
	~PlayerModelAnimator() = default;

	void Update() override;

private:

	PlayerAnimation mCurrentAnimation;

	Player* mPlayer;
};
