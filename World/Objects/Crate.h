#pragma once

#include "../GameObject.h"

class ModelRenderer;
class Collider3D;

class Crate : public GameObject
{
public:

	Crate();
	~Crate();

	void Init() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void OnCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	/// <summary>
	/// 吸い込みに耐えるタイマー
	/// </summary>
	float mEnduranceTimer;

	bool mIsHitTornado;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collider3D> mCollider;
};
