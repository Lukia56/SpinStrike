#pragma once

#include "../GameObject.h"
#include <vector>
#include "Camera/CameraProperty.h"
#include "Param/Param.h"

struct PlayerParam;
struct AABBColliderParam;
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

	Player(std::shared_ptr<Resource::ResourceBase> model, const PlayerParam& param, const std::vector<AABBColliderParam>& aabbParam, GameObject* tornado);
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

	void SpinAction(float deltaTime);

	void ActivateSpin(float deltaTime);

	void DeactivateSpin();

	void EndSpin();

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

	bool mIsSpinning;

	float mSpinStamina;

	float mSpinPreStartTimer;

	float mSpinCooldownTimer;

	PlayerParam mParam;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<ModelAnimator> mAnimator;
	
	std::vector<std::unique_ptr<Collider3D>> mColliders;

	GameObject* mTornado;

	Camera::View mCameraView;
};
