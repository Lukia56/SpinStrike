#pragma once

#include "../GameObject.h"
#include <stack>
#include <vector>

class PlayerBullet;

class PlayerBulletManager : public GameObject
{
public:

	PlayerBulletManager(int maxNum);
	~PlayerBulletManager() = default;

	void Init() override;

	void Update() override;

	void CreateBullet(const Vector3& pos, const Vector3& moveVec);

private:

	GameObject* mActiveBulletRoot;
	GameObject* mPoolBulletRoot;

	std::vector<PlayerBullet*> mActiveBullets;
	std::stack<PlayerBullet*> mPoolBullets;
};
