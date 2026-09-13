#pragma once

#include "../GameObject.h"
#include <vector>

struct EnemyPatrollingData;
struct WaypointGroup;
class Collider3D;
template <class T>
class StateContext;

class Enemy : public GameObject
{
public:

	Enemy(Transform* playerTransform, EnemyPatrollingData patrollingData, const std::vector<WaypointGroup>& waypointGroups);
	~Enemy() = default;

	void Init() override;

	void Finalize() override;

	void Update() override;

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	const Vector3& GetVelocity() const { return mVelocity; }
	void SetVelocity(const Vector3& vel) { mVelocity = vel; }

	int GetCurrentWaypointID() const { return mCurrentWaypointID; }
	void SetCurrentWaypointID(int waypointID) { mCurrentWaypointID = waypointID; }

	Transform* GetPlayerTransform() const { return mPlayerTransform; }

private:

	void ResolvePush();

private:

	Vector3 mVelocity;

	Vector3 mMoveVec;

	Vector3 mCollisionPush;

	/// <summary>
	/// 吸い込みに耐えるタイマー
	/// </summary>
	float mEnduranceTimer;

	bool mIsHitTornado;

	int mCurrentWaypointID;

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<StateContext<Enemy>> mStateContext;

	Transform* mPlayerTransform;
};
