#pragma once

#include "../GameObject.h"

class PlayerBulletManager : public GameObject
{
public:

	PlayerBulletManager();
	~PlayerBulletManager() = default;

	void Init() override;

	void Update() override;

	void CreateBullet(const Vector3& pos, const Vector3& moveVec);
};
