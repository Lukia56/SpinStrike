#pragma once

#include "../GameObject.h"

namespace Collision
{
	class AABB3D;
}

class PlayerTornado : public GameObject
{
public:

	PlayerTornado();
	~PlayerTornado();

	void Init() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

public:

	void SetSpinningFlag(const bool flag);

private:

	bool mIsSpinning;

	std::unique_ptr<Collision::AABB3D> mCollider;
};
