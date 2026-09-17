#pragma once

#include "../IState.h"
#include "Param/Param.h"

class Enemy;

class StateEnemyPatrollingMove : public IState<Enemy>
{
public:

	StateEnemyPatrollingMove(WaypointMoveData& moveData, const WaypointGroup& waypointGroup);
	~StateEnemyPatrollingMove() = default;

	void Enter(Enemy& owner) override;

	void Update(Enemy& owner, StateContext<Enemy>& context) override;

	void Exit(Enemy& owner) override;

private:

	Vector3 CalculateNextWaypointNormal(Enemy& enemy);

	int GetNextWaypointID(Enemy& enemy);

	bool IsReachWaypoint(Enemy& enemy);

private:

	int mWaypointGroupID;

	bool mIsLoop;

	bool mIsFlipped;

	Vector3 mMoveDir;

	Vector3 mMoveStartPos;

	WaypointGroup mWaypointGroup;
};
