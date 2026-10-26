#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyAttack : public IState<Enemy>
{
public:

	StateEnemyAttack();
	~StateEnemyAttack() = default;

	void Enter(Enemy& enemy) override;

	void Update(Enemy& enemy, StateContext<Enemy>& context) override;

	void Exit(Enemy& enemy) override;

private:

	float mAttackCooldownTimer;
};
