#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyDamage : public IState<Enemy>
{
public:

	StateEnemyDamage();
	~StateEnemyDamage() = default;

	void Enter(Enemy& enemy) override;

	void Update(Enemy& enemy, StateContext<Enemy>& context) override;

	void Exit(Enemy& enemy) override;

private:

	float mStunTimer;
};
