#pragma once

#include "../GameObject.h"
#include "Camera/CameraProperty.h"
#include "Param/Param.h"

class PlayerTornado;
class ModelRenderer;
class Collider3D;
class ModelAnimator;
namespace Resource
{
	class ResourceBase;
}

class Player : public GameObject
{
public:

	Player(std::shared_ptr<Resource::ResourceBase> model, std::shared_ptr<Resource::ResourceBase> shadowTexture, const PlayerParam& param, const std::vector<AABBColliderParam>& aabbParam, const PlayerInitData& initData, std::unique_ptr<PlayerTornado> tornado);
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

	int mHP;

	float mInvincibleTimer;

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

	std::unique_ptr<ModelAnimator> mAnimator;
	
	std::vector<std::unique_ptr<Collider3D>> mColliders;

	PlayerTornado* mTornado;

	Camera::View mCameraView;
};
