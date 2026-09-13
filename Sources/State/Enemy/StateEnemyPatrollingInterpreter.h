#pragma once

#include "../IState.h"
#include <vector>

struct WaypointActionData;
class Enemy;

/// <summary>
/// 敵のウェイポイント到着時の行動データを読み取って実行する
/// </summary>
class StateEnemyPatrollingInterpreter : public IState<Enemy>
{
public:
	
	StateEnemyPatrollingInterpreter(std::vector<WaypointActionData> actionData);
	~StateEnemyPatrollingInterpreter() = default;

	void Enter(Enemy& owner) override;

	void Update(Enemy& owner, StateContext<Enemy>& context) override;

	void Exit(Enemy& owner) override;

private:

	int mActionIndex;

	int mActionDataIndex;

	std::vector<WaypointActionData> mActionData;
};
