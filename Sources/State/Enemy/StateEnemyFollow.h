#pragma once

#include "../IState.h"

class Enemy;
class EnemyModelAnimator;

/// <summary>
/// ÉvÉåÉCÉÑÅ[Çí«ê’Ç∑ÇÈ
/// </summary>
class StateEnemyFollow : public IState<Enemy>
{
public:

	StateEnemyFollow(EnemyModelAnimator* modelAnimator);
	~StateEnemyFollow() = default;

	void Enter(Enemy& enemy) override;

	void Update(Enemy& enemy, StateContext<Enemy>& context) override;

	void Exit(Enemy& enemy) override;

private:

	void CountLostTimer(const Enemy& enemy);

	bool IsLostPlayer() const;

private:

	float mLostTimer;

	EnemyModelAnimator* mModelAnimator;
};
