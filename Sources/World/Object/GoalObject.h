#pragma once

#include "../GameObject.h"

class Collider3D;

class GoalObject : public GameObject
{
public:

	GoalObject();
	~GoalObject() = default;

	void Init() override;
	void Update() override;
	void DebugDraw() override;

private:

	std::unique_ptr<Collider3D> mCollider;
};
