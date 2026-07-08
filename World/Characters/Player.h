#pragma once

#include "../GameObject.h"
#include "Camera/CameraProperty.h"

class PlayerTornado;
class PlayerBulletManager;
class ModelRenderer;

namespace Collision
{
	class AABB3D;
}

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

	void OnCollision(GameObject* other, const Collision::Result& result, Collision::Tag tag) override;

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

	float mCanJumpTimer;

	bool mIsJumping;

	bool mOnGround;

	bool mOnWall;

	float mIgnoreMoveInputTimer;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collision::AABB3D> mCollider;

	PlayerTornado* mTornado;

	Camera::View mCameraView;
};
