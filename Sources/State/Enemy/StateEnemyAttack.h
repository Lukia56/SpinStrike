#pragma once

#include "../IState.h"

class Enemy;
class EnemyModelAnimator;

class StateEnemyAttack : public IState<Enemy>
{
public:

	StateEnemyAttack(EnemyModelAnimator* modelAnimator);
	~StateEnemyAttack() = default;

	void Enter(Enemy& enemy) override;

	void Update(Enemy& enemy, StateContext<Enemy>& context) override;

	void Exit(Enemy& enemy) override;

private:

	float mAttackCooldownTimer;

	EnemyModelAnimator* mModelAnimator;
};
