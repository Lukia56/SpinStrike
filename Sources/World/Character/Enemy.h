#pragma once

#include "../GameObject.h"

class Collider3D;
template <class T>
class StateContext;

class Enemy : public GameObject
{
public:

	Enemy(Transform* playerTransform);
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

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<StateContext<Enemy>> mStateContext;

	Transform* mPlayerTransform;
};
