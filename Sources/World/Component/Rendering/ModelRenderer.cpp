#include "ModelRenderer.h"
#include <DxLib.h>
#include "ModelInstance.h"
#include "System/Resource/ResourceBase.h"
#include "World/GameObject.h"

ModelRenderer::ModelRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource, std::shared_ptr<Resource::ResourceBase> animation) :
	Renderer(owner, resource),
	mModelInstance(nullptr),
	mAnimModel(animation)
{
	if (resource)
	{
		mModelInstance = std::make_unique<ModelInstance>(resource);
	}
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Draw() const
{
	if (!mOwner) return;
	if (!mResource) return;
	if (!mModelInstance) return;

	const VECTOR pos = (mOwner->GetTransform()->CalculateWorldPosition() + mOffsetPos).GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform()->CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform()->CalculateWorldScale().GetAsDxLibVector();

	int handle = mModelInstance->GetHandle();

	MV1SetPosition(handle, pos);
	MV1SetRotationXYZ(handle, rot);
	MV1SetScale(handle, scale);

	MV1DrawModel(handle);
}

void ModelRenderer::DisableMovement(const std::string& rootName)
{
	if (!mModelInstance) return;

	int handle = mModelInstance->GetHandle();

	int rootFrameIndex = MV1SearchFrame(handle, rootName.c_str());
	MATRIX rootMtx = MV1GetFrameLocalMatrix(handle, rootFrameIndex);
	MV1SetFrameUserLocalMatrix(handle, rootFrameIndex, rootMtx);
}

int ModelRenderer::GetModelHandle() const
{
	if (!mModelInstance) return -1;

	return mModelInstance->GetHandle();
}

int ModelRenderer::GetAnimModelHandle() const
{
	if (!mAnimModel) return GetModelHandle();
	
	return mAnimModel->GetHandle();
}
