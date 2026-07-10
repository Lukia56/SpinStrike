#pragma once

#include "../GameObject.h"
#include "Camera/CameraProperty.h"

class PlayerTornado;
class PlayerBulletManager;
class ModelRenderer;
class Collider3D;

class Player : public GameObject
{
public:

	Player(PlayerBulletManager* bulletManager);
	~Player();

	void Init() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

	bool CanJump();

	bool CanCancelJump();

private:

	Vector3 mVelocity;

	Vector3 mLastMoveVec;

	Vector3 mLastCollideNormal;

	float mCanJumpTimer;

	bool mIsJumping;

	bool mOnGround;

	bool mOnWall;

	float mStickWallCancelTimer;

	float mIgnoreMoveInputTimer;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collider3D> mCollider;

	PlayerTornado* mTornado;

	Camera::View mCameraView;
};
