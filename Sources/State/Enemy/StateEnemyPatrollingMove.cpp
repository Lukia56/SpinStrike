#include "StateEnemyPatrollingMove.h"
#include "Param/Param.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;
}

StateEnemyPatrollingMove::StateEnemyPatrollingMove(WaypointMoveData& moveData, const WaypointGroup& waypointGroup) :
	mWaypointGroupID(moveData.waypointGroupID),
	mCurrentWaypointID(0),
	mIsLoop(moveData.isLoop),
	mWaypointGroup(waypointGroup)
{
}

void StateEnemyPatrollingMove::Enter(Enemy& owner)
{
	if (mWaypointGroup.waypoints.empty()) return;

	Vector3 distance = CalculateNextWaypointDistance(owner.GetTransform());

	mMoveStartPos = owner.GetTransform()->CalculateWorldPosition();

	mMoveDir = distance.GetNormalize();
}

void StateEnemyPatrollingMove::Update(Enemy& owner, StateContext<Enemy>& context)
{
	if (mWaypointGroup.waypoints.empty()) return;

	owner.SetVelocity(mMoveDir * kMoveSpeed);

	if (IsReachWaypoint(owner.GetTransform()))
	{
		mCurrentWaypointID = GetNextWaypointID();

		Vector3 distance = CalculateNextWaypointDistance(owner.GetTransform());

		mMoveStartPos = owner.GetTransform()->CalculateWorldPosition();

		mMoveDir = distance.GetNormalize();
	}
}

void StateEnemyPatrollingMove::Exit(Enemy& owner)
{

}

Vector3 StateEnemyPatrollingMove::CalculateNextWaypointDistance(Transform* transform)
{
	Vector3 startPos = transform->CalculateWorldPosition();
	Vector3 endPos = mWaypointGroup.waypoints[GetNextWaypointID()].position;

	return endPos - startPos;
}

int StateEnemyPatrollingMove::GetNextWaypointID() const
{
	int id = mCurrentWaypointID + 1;

	// 1Žü‚µ‚½‚çÅ‰‚©‚ç
	if (id >= mWaypointGroup.waypoints.size())
	{
		id = 0;
	}

	return id;
}

bool StateEnemyPatrollingMove::IsReachWaypoint(Transform* transform) const
{
	Vector3 goalWaypointPos = mWaypointGroup.waypoints[GetNextWaypointID()].position;

	float waypointSqDistance = (goalWaypointPos - mMoveStartPos).GetSqLength();
	float traveledSqDistance = (transform->CalculateWorldPosition() - mMoveStartPos).GetSqLength();

	return traveledSqDistance >= waypointSqDistance;
}
