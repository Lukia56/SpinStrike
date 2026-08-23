#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyPatrolling : public IState<Enemy>
{
public:

	StateEnemyPatrolling();
	~StateEnemyPatrolling() = default;

	void Enter(Enemy& owner) override;

	std::unique_ptr<IState<Enemy>> Update(Enemy& owner) override;

	void Exit(Enemy& owner) override;
};
