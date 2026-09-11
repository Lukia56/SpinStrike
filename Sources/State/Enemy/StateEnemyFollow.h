#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyFollow : public IState<Enemy>
{
public:

	StateEnemyFollow();
	~StateEnemyFollow() = default;

	void Enter(Enemy& owner) override;

	void Update(Enemy& owner, StateContext<Enemy>& context) override;

	void Exit(Enemy& owner) override;
};
