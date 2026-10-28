#pragma once

#include "../GameObject.h"
#include "PlayerAnimation.h"
#include "Camera/CameraProperty.h"

struct AnimationParam;
struct PlayerInitData;
class PlayerTornado;
class ModelRenderer;
class Collider3D;
class ModelAnimator;
namespace Resource
{
	class ResourceBase;
}
namespace Observer
{
	class Subject;
}

class Player : public GameObject
{
public:

	Player(std::shared_ptr<Resource::ResourceBase> model, std::shared_ptr<Resource::ResourceBase> shadowTexture, const PlayerInitData& initData, std::unique_ptr<PlayerTornado> tornado);
	~Player();

	void Init() override;

	void Finalize() override;

	void Update() override;

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	int GetHP() const { return mHP; }

	float GetSpinStamina() const;

	bool IsSpinning() const;

	Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void ResolvePush();

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

	void AnimationUpdate();

	bool CanJump() const;

	bool CanCancelJump() const;

	void Damage();

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

	PlayerAnimation mCurrentAnimation;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<ModelAnimator> mAnimator;
	
	std::vector<std::unique_ptr<Collider3D>> mColliders;

	std::unique_ptr<Observer::Subject> mEventSubject;

	PlayerTornado* mTornado;

	Camera::View mCameraView;
};
