#pragma once

#include "../GameObject.h"

class PlayerBulletManager;
class Collider3D;

class PlayerTornado : public GameObject
{
public:

	PlayerTornado(PlayerBulletManager* bulletManager);
	~PlayerTornado();

	void Init() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void DebugDraw() override;

	void CreateBullet(const Vector3& moveVec);

	void AddPulledNum() { mPulledNum++; }

public:

	void SetSpinningFlag(const bool flag);

private:

	bool mIsSpinning;

	/// <summary>
	/// ãzÇ¢çûÇÒÇæêî
	/// </summary>
	int mPulledNum;

	std::unique_ptr<Collider3D> mCollider;

	PlayerBulletManager* mBulletManager;
};
