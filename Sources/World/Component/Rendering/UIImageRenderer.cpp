#include "UIImageRenderer.h"
#include <DxLib.h>
#include "../RectTransform.h"
#include "Utility/Rect.h"
#include "Utility/Vector.h"

UIImageRenderer::UIImageRenderer(GameObject* owner, RectTransform* rectTransform) :
	Renderer(owner),
	mTexSize(Vector2::Zero),
	mRectTransform(rectTransform)
{
}

void UIImageRenderer::Load(const std::string& filePath)
{
	Renderer::Load(filePath);

	// “Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚½‚ç‘ŠúƒŠƒ^[ƒ“
	if (!mResource) return;

	GetGraphSizeF(mResource->GetHandle(), &mTexSize.x, &mTexSize.y);
}

void UIImageRenderer::Draw() const
{
	if (!mOwner) return;
	if (!mResource) return;
	if (!mRectTransform) return;

	Rect rect = mRectTransform->CalculateRect();

	DrawModiGraphF(
		rect.xMin, rect.yMin,
		rect.xMin + rect.width, rect.yMin,
		rect.xMin + rect.width, rect.yMin + rect.height,
		rect.xMin, rect.yMin + rect.height,
		mResource->GetHandle(), true);
}
