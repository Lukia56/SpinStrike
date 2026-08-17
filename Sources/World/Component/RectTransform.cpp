#include "RectTransform.h"
#include "Utility/Math.h"
#include "Utility/Rect.h"
#include "Utility/Vector.h"

namespace
{
	constexpr Vector2 kInitAnchor{ 0.5f, 0.5f };
	constexpr Vector2 kInitPivot{ 0.5f, 0.5f };
}

RectTransform::RectTransform(GameObject* owner) :
	Transform(owner),
	mSizeDelta(Vector2::Zero),
	mOffsetMin(Vector2::Zero),
	mOffsetMax(Vector2::Zero),
	mAnchorMin(kInitAnchor),
	mAnchorMax(kInitAnchor),
	mPivot(kInitPivot),
	mParentRect(nullptr)
{
}

Rect RectTransform::CalculateRect()
{
	Rect rectParent = mParentRect ? mParentRect->CalculateRect() : Rect{};

	Rect rectResult{};

	CalculateRectX(rectResult, rectParent);
	CalculateRectY(rectResult, rectParent);

	return rectResult;
}

void RectTransform::SetFullRectAsFixed(const Vector2& size)
{
	mSizeDelta = size;
}

void RectTransform::SetRectWidthAsFixed(float width)
{
	mSizeDelta.x = width;
}

void RectTransform::SetRectHeightAsFixed(float height)
{
	mSizeDelta.y = height;
}

void RectTransform::SetFullRectAsStretch(float left, float top, float right, float bottom)
{
	mOffsetMin = Vector2(left, top);
	mOffsetMax = Vector2(right, bottom);
}

void RectTransform::SetRectXAsStretch(float left, float right)
{
	mOffsetMin.x = left;
	mOffsetMax.x = right;
}

void RectTransform::SetRectYAsStretch(float top, float bottom)
{
	mOffsetMin.y = top;
	mOffsetMax.y = bottom;
}

void RectTransform::SetAnchor(const Vector2& anchorMin, const Vector2& anchorMax)
{
	mAnchorMin = anchorMin;
	mAnchorMax = anchorMax;
}
void RectTransform::SetAnchor(Anchor anchor)
{
	switch (anchor)
	{
	case Anchor::LeftTop:
		mAnchorMin = mAnchorMax = Vector2(0.0f, 0.0f);
		break;
	case Anchor::CenterTop:
		mAnchorMin = mAnchorMax = Vector2(0.5f, 0.0f);
		break;
	case Anchor::RightTop:
		mAnchorMin = mAnchorMax = Vector2(1.0f, 0.0f);
		break;
	case Anchor::LeftMiddle:
		mAnchorMin = mAnchorMax = Vector2(0.0f, 0.5f);
		break;
	case Anchor::CenterMiddle:
		mAnchorMin = mAnchorMax = Vector2(0.5f, 0.5f);
		break;
	case Anchor::RightMiddle:
		mAnchorMin = mAnchorMax = Vector2(1.0f, 0.5f);
		break;
	case Anchor::LeftBottom:
		mAnchorMin = mAnchorMax = Vector2(0.0f, 1.0f);
		break;
	case Anchor::CenterBottom:
		mAnchorMin = mAnchorMax = Vector2(0.5f, 1.0f);
		break;
	case Anchor::RightBottom:
		mAnchorMin = mAnchorMax = Vector2(1.0f, 1.0f);
		break;
	case Anchor::LeftStretch:
		mAnchorMin = Vector2(0.0f, 0.0f);
		mAnchorMax = Vector2(0.0f, 1.0f);
		break;
	case Anchor::CenterStretch:
		mAnchorMin = Vector2(0.5f, 0.0f);
		mAnchorMax = Vector2(0.5f, 1.0f);
		break;
	case Anchor::RightStretch:
		mAnchorMin = Vector2(1.0f, 0.0f);
		mAnchorMax = Vector2(1.0f, 1.0f);
		break;
	case Anchor::TopStretch:
		mAnchorMin = Vector2(0.0f, 0.0f);
		mAnchorMax = Vector2(1.0f, 0.0f);
		break;
	case Anchor::MiddleStretch:
		mAnchorMin = Vector2(0.0f, 0.5f);
		mAnchorMax = Vector2(1.0f, 0.5f);
		break;
	case Anchor::BottomStretch:
		mAnchorMin = Vector2(0.0f, 1.0f);
		mAnchorMax = Vector2(1.0f, 1.0f);
		break;
	case Anchor::FullStretch:
		mAnchorMin = Vector2(0.0f, 0.0f);
		mAnchorMax = Vector2(1.0f, 1.0f);
		break;
	}
}

void RectTransform::OnUpdateParent()
{
	mParentRect = dynamic_cast<RectTransform*>(GetParent());
}

void RectTransform::CalculateRectX(Rect& rectResult, const Rect& rectParent)
{
	// 親のサイズに合わせて引き伸ばす
	if (IsXAxisStretch())
	{
		float minAnchoredPosX = rectParent.xMin + rectParent.width * mAnchorMin.x;
		float maxAnchoredPosX = rectParent.xMin + rectParent.width * mAnchorMax.x;

		mSizeDelta.x = mOffsetMax.x - mOffsetMin.x;

		rectResult.xMin = minAnchoredPosX + mOffsetMin.x;
		rectResult.width = maxAnchoredPosX - minAnchoredPosX + mSizeDelta.x;
	}
	// サイズと基準点からの距離を固定する
	else
	{
		float anchoredPosX = rectParent.xMin + rectParent.width * mAnchorMin.x;

		mOffsetMin.x = -mSizeDelta.x * mPivot.x;
		mOffsetMax.x = mSizeDelta.x * (1.0f - mPivot.x);

		rectResult.xMin = localPosition.x + anchoredPosX + mOffsetMin.x;
		rectResult.width = mOffsetMax.x - mOffsetMin.x;
	}
}

void RectTransform::CalculateRectY(Rect& rectResult, const Rect& rectParent)
{
	// 親のサイズに合わせて引き伸ばす
	if (IsYAxisStretch())
	{
		float minAnchoredPosY = rectParent.yMin + rectParent.height * mAnchorMin.y;
		float maxAnchoredPosY = rectParent.yMin + rectParent.height * mAnchorMax.y;

		mSizeDelta.y = mOffsetMax.y - mOffsetMin.y;

		rectResult.yMin = minAnchoredPosY + mOffsetMin.y;
		rectResult.height = maxAnchoredPosY - minAnchoredPosY + mSizeDelta.y;
	}
	// サイズと基準点からの距離を固定する
	else
	{
		float anchoredPosY = rectParent.yMin + rectParent.height * mAnchorMin.y;

		mOffsetMin.y = -mSizeDelta.y * mPivot.y;
		mOffsetMax.y = mSizeDelta.y * (1.0f - mPivot.y);

		rectResult.yMin = localPosition.y + anchoredPosY + mOffsetMin.y;
		rectResult.height = mOffsetMax.y - mOffsetMin.y;
	}
}

bool RectTransform::IsXAxisStretch()
{
	return !Math::NearlyEqual(mAnchorMin.x, mAnchorMax.x);
}

bool RectTransform::IsYAxisStretch()
{
	return !Math::NearlyEqual(mAnchorMin.y, mAnchorMax.y);
}
