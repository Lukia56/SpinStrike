#pragma once

#include "../GameObject.h"

class Collider3D;

class EnemyAttackCollider : public GameObject
{
public:

	EnemyAttackCollider(float attackRadius);
	~EnemyAttackCollider() = default;

	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void DebugDraw() override;

	void Setup(float duration);

private:

	float mActiveTimer;

	std::unique_ptr<Collider3D> mCollider;
};
