#pragma once

#include "../GameObject.h"

class Collider3D;

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

	Transform* mPlayerTransform;
};
