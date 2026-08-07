#include "ModelRenderer.h"
#include <DxLib.h>
#include "../../GameObject.h"

ModelRenderer::ModelRenderer(GameObject* owner) :
	Renderer(owner),
	mModelHandle(-1)
{
}

ModelRenderer::~ModelRenderer()
{
	MV1DeleteModel(mModelHandle);
}

void ModelRenderer::Load(const std::string& filePath)
{
	Renderer::Load(filePath);

	if (!mResource) return;

	mModelHandle = mResource->GetHandle();
}

void ModelRenderer::Draw()
{
	if (!mOwner) return;
	if (!mResource) return;

	const VECTOR pos = (mOwner->GetTransform().CalculateWorldPosition() + mOffsetPos).GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform().CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform().CalculateWorldScale().GetAsDxLibVector();

	MV1SetPosition(mModelHandle, pos);
	MV1SetRotationXYZ(mModelHandle, rot);
	MV1SetScale(mModelHandle, scale);

	MV1DrawModel(mModelHandle);
}

void ModelRenderer::DisableMovement(const std::string& rootName)
{
	int rootFrameIndex = MV1SearchFrame(mModelHandle, rootName.c_str());

	MATRIX rootMtx = MV1GetFrameLocalMatrix(mModelHandle, rootFrameIndex);

	MV1SetFrameUserLocalMatrix(mModelHandle, rootFrameIndex, rootMtx);
}
