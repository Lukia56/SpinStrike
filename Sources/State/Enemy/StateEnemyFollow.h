#pragma once

#include "../IState.h"

class Enemy;

/// <summary>
/// ƒvƒŒƒCƒ„[‚ğ’ÇÕ‚·‚é
/// </summary>
class StateEnemyFollow : public IState<Enemy>
{
public:

	StateEnemyFollow();
	~StateEnemyFollow() = default;

	void Enter(Enemy& enemy) override;

	void Update(Enemy& enemy, StateContext<Enemy>& context) override;

	void Exit(Enemy& enemy) override;

private:

	void CountLostTimer(const Enemy& enemy);

	bool IsLostPlayer() const;

private:

	float mLostTimer;
};
