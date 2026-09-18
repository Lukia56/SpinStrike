#include "UIImageRenderer.h"
#include <DxLib.h>
#include "../RectTransform.h"
#include "System/Resource/ResourceBase.h"
#include "Utility/Rect.h"
#include "Utility/Vector.h"

UIImageRenderer::UIImageRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource, RectTransform* rectTransform) :
	Renderer(owner, resource),
	mTexSize(Vector2::Zero),
	mRectTransform(rectTransform)
{
	if (resource)
	{
		GetGraphSizeF(resource->GetHandle(), &mTexSize.x, &mTexSize.y);
	}
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

Vector2 UIImageRenderer::GetTexSize() const
{
	Vector3 worldScale = mRectTransform->CalculateWorldScale();

	Vector2 size{};
	size.x = mTexSize.x * worldScale.x;
	size.y = mTexSize.y * worldScale.y;

	return size;
}
