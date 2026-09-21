#include "ModelTest.h"
#include "../Component/ModelAnimator.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "Param/Param.h"

ModelTest::ModelTest(std::shared_ptr<Resource::ResourceBase> model, std::shared_ptr<Resource::ResourceBase> anim, int index) :
	mModel(nullptr)
{
	mModel = std::make_unique<ModelRenderer>(this, model, anim);

	mAnimator = std::make_unique<ModelAnimator>(mModel.get(), 30.0f);
	mAnimator->Play(AnimationParam{ .animIndex = index, .isLoop = true, .isForcePlay = false });
}

void ModelTest::Init()
{
}

void ModelTest::Update()
{
	mAnimator->Update();
}

void ModelTest::Draw()
{
	mModel->Draw();
}
