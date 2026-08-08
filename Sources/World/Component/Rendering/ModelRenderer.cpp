#include "ModelRenderer.h"
#include <DxLib.h>
#include "ModelInstance.h"
#include "../../GameObject.h"
#include "System/Resource/Model.h"

ModelRenderer::ModelRenderer(GameObject* owner) :
	Renderer(owner),
	mModelInstance(nullptr)
{
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Load(const std::string& filePath)
{
	Renderer::Load(filePath);

	if (!mResource) return;

	mModelInstance = std::make_unique<ModelInstance>(mResource);
}

void ModelRenderer::Draw()
{
	if (!mOwner) return;
	if (!mResource) return;
	if (!mModelInstance) return;

	const VECTOR pos = (mOwner->GetTransform().CalculateWorldPosition() + mOffsetPos).GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform().CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform().CalculateWorldScale().GetAsDxLibVector();

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

int ModelRenderer::GetHandle()
{
	if (!mModelInstance) return -1;

	return mModelInstance->GetHandle();
}
