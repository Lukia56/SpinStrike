#include "ModelRenderer.h"
#include <DxLib.h>
#include "../../GameObject.h"
#include "System/Resource/Resource.h"

ModelRenderer::ModelRenderer(GameObject* owner) :
	Renderer(owner),
	mModelHandle(-1)
{
}

void ModelRenderer::Load(const std::string& filePath)
{
	Renderer::Load(filePath);

	mModelHandle = mResource->GetHandle();
}

void ModelRenderer::Draw()
{
	if (!mOwner) return;
	if (!mResource) return;

	const VECTOR pos = mOwner->GetTransform().CalculateWorldPosition().GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform().CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform().CalculateWorldScale().GetAsDxLibVector();

	MV1SetPosition(mModelHandle, pos);
	MV1SetRotationXYZ(mModelHandle, rot);
	MV1SetScale(mModelHandle, scale);

	MV1DrawModel(mModelHandle);
}
