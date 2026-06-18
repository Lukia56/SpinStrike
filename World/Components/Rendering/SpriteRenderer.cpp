#include "SpriteRenderer.h"
#include <DxLib.h>
#include "../../GameObject.h"
#include "System/Resource/Resource.h"

SpriteRenderer::SpriteRenderer(GameObject* owner) :
	Renderer(owner),
	mTexHalfSize(Vector2::One)
{
}

void SpriteRenderer::Load(const std::string& filePath)
{
	Renderer::Load(filePath);

	// “Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚½‚ç‘ŠúƒŠƒ^[ƒ“
	if (!mResource) return;

	// ‰æ‘œ‚Ì”¼Œa‚ðŽæ“¾
	GetGraphSizeF(mResource->GetHandle(), &mTexHalfSize.x, &mTexHalfSize.y);
	mTexHalfSize *= 0.5f;
}

void SpriteRenderer::Draw()
{
	if (!mOwner) return;
	if (!mResource) return;

	const VECTOR pos = mOwner->GetTransform().CalculateWorldPosition().GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform().CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform().CalculateWorldScale().GetAsDxLibVector();

	DrawRotaGraphFast3F(pos.x, pos.y, mTexHalfSize.x, mTexHalfSize.y, scale.x, scale.y, rot.z, mResource->GetHandle(), true);
}
