#pragma once

#include "../GameObject.h"
#include "Camera/CameraProperty.h"
#include "Param/Param.h"

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

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void ResolvePush();

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

	bool CanJump() const;

	bool CanCancelJump() const;

private:

	Vector3 mVelocity;

	Vector3 mLastMoveVec;

	Vector3 mLastCollideNormal;

	Vector3 mCollisionPush;

	float mCanJumpTimer;

	bool mIsJumping;

	bool mOnGround;

	bool mOnWall;

	bool mOnCancelStickWall;

	float mStickWallCancelTimer;

	float mIgnoreMoveInputTimer;

	PlayerParam mParam;

	std::unique_ptr<ModelRenderer> mModel;
	
	std::vector<std::unique_ptr<Collider3D>> mColliders;

	PlayerTornado* mTornado;

	Camera::View mCameraView;
};
