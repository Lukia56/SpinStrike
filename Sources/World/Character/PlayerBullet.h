#pragma once

#include "../GameObject.h"

class PlayerBullet : public GameObject
{
public:

	PlayerBullet();
	~PlayerBullet() = default;

	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void DebugDraw() override;

	void Setup(const Vector3& pos, const Vector3& moveVec);

public:

	float GetDestroyTimer() const { return mDestroyTimer; }

private:

	float mDestroyTimer;

	Vector3 mMoveVec;
};
