#pragma once

#include "../GameObject.h"

class Collider3D;
class ModelRenderer;
namespace Resource
{
	class ResourceBase;
}

class GoalObject : public GameObject
{
public:

	GoalObject(std::shared_ptr<Resource::ResourceBase> model);
	~GoalObject() = default;

	void Init() override;
	void Update() override;
	void Draw() override;
	void DebugDraw() override;

private:

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<ModelRenderer> mModel;
};
