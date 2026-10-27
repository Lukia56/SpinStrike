#pragma once

#include "../GameObject.h"

class PlayerBulletManager;
class Collider3D;

class PlayerTornado : public GameObject
{
public:

	PlayerTornado(PlayerBulletManager* bulletManager);
	~PlayerTornado() = default;

	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void Draw() override;
	void DebugDraw() override;

	void AddPulledNum() { mPulledNum++; }

public:

	bool IsSpinning() const { return mIsSpinning; }

	float GetSpinStamina() const { return mSpinStamina; }

private:

	void SpinAction(float deltaTime);

	void ActivateSpin(float deltaTime);

	void StartSpin();

	void DeactivateSpin();

	void EndSpin();

	void CreateBullet();

private:

	bool mIsSpinning;

	float mSpinStamina;

	float mSpinPreStartTimer;

	float mSpinCooldownTimer;

	/// <summary>
	/// ãzÇ¢çûÇÒÇæêî
	/// </summary>
	int mPulledNum;

	std::unique_ptr<Collider3D> mAttackCollider;

	PlayerBulletManager* mBulletManager;
};
