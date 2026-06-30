#pragma once

#include "../GameObject.h"

class ModelRenderer;

namespace Collision3D
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

private:

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collision3D::AABB3D> mCollider;
};
