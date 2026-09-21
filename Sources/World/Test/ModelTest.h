#pragma once

#include "../GameObject.h"

class ModelRenderer;
class ModelAnimator;
namespace Resource
{
	class ResourceBase;
}

class ModelTest : public GameObject
{
public:

	ModelTest(std::shared_ptr<Resource::ResourceBase> model, std::shared_ptr<Resource::ResourceBase> anim, int index);
	~ModelTest() = default;

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<ModelRenderer> mModel;
	std::unique_ptr<ModelAnimator> mAnimator;
};
