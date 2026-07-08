#pragma once

#include "../GameObject.h"

class ModelRenderer;

namespace Collision
{
	class AABB3D;
}

class Crate : public GameObject
{
public:

	Crate();
	~Crate();

	void Init() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void OnCollision(GameObject* other, const Collision::Result& result, Collision::Tag tag) override;

private:

	/// <summary>
	/// 吸い込みに耐えるタイマー
	/// </summary>
	float mEnduranceTimer;

	bool mIsHitTornado;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collision::AABB3D> mCollider;
};
