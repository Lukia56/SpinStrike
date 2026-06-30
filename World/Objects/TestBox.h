#pragma once

#include "../GameObject.h"

namespace Collision
{
	class AABB3D;
}

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

	std::unique_ptr<Collision::AABB3D> mCollider;
};
