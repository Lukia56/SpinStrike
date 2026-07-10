#pragma once

#include "../GameObject.h"

class Collider3D;

class TestBox : public GameObject
{
public:

	TestBox();
	~TestBox();

	void Init() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

private:

	std::unique_ptr<Collider3D> mCollider;
};
