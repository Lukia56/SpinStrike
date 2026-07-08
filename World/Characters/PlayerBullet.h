#pragma once

#include "../GameObject.h"

class PlayerBullet : public GameObject
{
public:

	PlayerBullet(const Vector3& moveVec);
	~PlayerBullet() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

private:

	Vector3 mMoveVec;
};
