#pragma once

#include "../IState.h"

class Enemy;

class StateEnemyFollow : public IState<Enemy>
{
public:

	StateEnemyFollow();
	~StateEnemyFollow() = default;

	void Enter(Enemy& owner) override;

	std::unique_ptr<IState<Enemy>> Update(Enemy& owner) override;

	void Exit(Enemy& owner) override;
};
