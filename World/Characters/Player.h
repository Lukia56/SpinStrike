#pragma once

#include "../GameObject.h"
#include "Camera/CameraProperty.h"

class ModelRenderer;

namespace Collision3D
{
	class AABB3D;
}

class Player : public GameObject
{
public:

	Player();
	~Player();

	void Init() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

private:

	Vector3 mVelocity;

	bool mIsJumping;

	bool mOnGround;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collision3D::AABB3D> mCollider;

	Camera::View mCameraView;
};
