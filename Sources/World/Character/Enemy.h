#pragma once

#include "../GameObject.h"

class Collider3D;

class Enemy : public GameObject
{
public:

	Enemy();
	~Enemy() = default;

	void Init() override;

	void Finalize() override;

	void PhysicsUpdate() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	std::unique_ptr<Collider3D> mCollider;
};
