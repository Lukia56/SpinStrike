#include "StateEnemyPatrollingMove.h"
#include "StateEnemyPatrollingInterpreter.h"
#include "../StateContext.h"
#include "Param/Param.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;
}

StateEnemyPatrollingMove::StateEnemyPatrollingMove(WaypointMoveData& moveData, const WaypointGroup& waypointGroup) :
	mWaypointGroupID(moveData.waypointGroupID),
	mIsLoop(moveData.isLoop),
	mIsFlipped(false),
	mWaypointGroup(waypointGroup)
{
}

void StateEnemyPatrollingMove::Enter(Enemy& owner)
{
	if (mWaypointGroup.waypoints.empty()) return;

	mMoveStartPos = owner.GetTransform()->CalculateWorldPosition();

	mMoveDir = CalculateNextWaypointNormal(owner);
}

void StateEnemyPatrollingMove::Update(Enemy& owner, StateContext<Enemy>& context)
{
	if (mWaypointGroup.waypoints.empty()) return;

	owner.SetVelocity(mMoveDir * kMoveSpeed);

	if (IsReachWaypoint(owner))
	{
		context.PushState<StateEnemyPatrollingInterpreter>();
		return;
	}
}

void StateEnemyPatrollingMove::Exit(Enemy& owner)
{
	owner.SetCurrentWaypointID(GetNextWaypointID(owner));
	owner.SetVelocity(Vector3::Zero);
}

Vector3 StateEnemyPatrollingMove::CalculateNextWaypointNormal(Enemy& enemy)
{
	Vector3 startPos = enemy.GetTransform()->CalculateWorldPosition();
	Vector3 endPos = mWaypointGroup.waypoints[GetNextWaypointID(enemy)].position;

	return (endPos - startPos).GetNormalize();
}

int StateEnemyPatrollingMove::GetNextWaypointID(Enemy& enemy)
{
	int id = enemy.GetCurrentWaypointID();

	size_t waypointNum = mWaypointGroup.waypoints.size();

	if (mIsLoop)
	{
		id++;
		id = (id + waypointNum) % waypointNum;
	}
	else
	{
		if (!mIsFlipped) id++;
		else id--;

		if (!mIsFlipped && id >= waypointNum)
		{
			id = waypointNum - 2;
			mIsFlipped = true;
		}
		if (id < 0)
		{
			id = 1;
			mIsFlipped = false;
		}
	}

	return id;
}

bool StateEnemyPatrollingMove::IsReachWaypoint(Enemy& enemy)
{
	Vector3 goalWaypointPos = mWaypointGroup.waypoints[GetNextWaypointID(enemy)].position;

	float waypointSqDistance = (goalWaypointPos - mMoveStartPos).GetSqLength();
	float traveledSqDistance = (enemy.GetTransform()->CalculateWorldPosition() - mMoveStartPos).GetSqLength();

	return traveledSqDistance >= waypointSqDistance;
}
