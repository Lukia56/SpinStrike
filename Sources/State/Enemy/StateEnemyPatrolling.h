#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyPatrolling : public IState<Enemy>
{
public:

	StateEnemyPatrolling();
	~StateEnemyPatrolling() = default;

	void Enter(Enemy& owner) override;

	void Update(Enemy& owner, StateContext<Enemy>& context) override;

	void Exit(Enemy& owner) override;
};
