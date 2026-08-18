#include "TextRenderer.h"
#include <DxLib.h>
#include "TextAlignment.h"
#include "../RectTransform.h"
#include "../../GameObject.h"
#include "Utility/Color.h"
#include "Utility/Rect.h"

TextRenderer::TextRenderer(GameObject* owner, RectTransform* rectTransform, const std::string& displayText, const Color& color, HolizontalAlignment hAlign, VerticalAlignment vAlign) :
	Renderer(owner),
	mDisplayText(displayText),
	mColor(color),
	mHolizontalAlignment(hAlign),
	mVerticalAlignment(vAlign),
	mRectTransform(rectTransform)
{
}

void TextRenderer::Draw() const
{
	if (!mOwner) return;

	Rect rect = mRectTransform->CalculateRect();
	rect.xMin += mOffsetPos.x;
	rect.yMin += mOffsetPos.y;
	
	Vector2 pos = Vector2(CalculateStartPosX(rect), CalculateStartPosY(rect));

	// フォントが読み込まれていたらフォントを使用してテキストを表示する
	if (mResource)
	{
		DrawStringFToHandle(pos.x, pos.y, mDisplayText.c_str(), mColor.GetAsHexRGB(), mResource->GetHandle());
	}
	// フォントが読み込まれていなかったらデフォルトのフォントを使用してテキストを表示する
	else
	{
		DrawStringF(pos.x, pos.y, mDisplayText.c_str(), mColor.GetAsHexRGB());
	}
}

int TextRenderer::CalculateStartPosX(const Rect& rect) const
{
	if (mHolizontalAlignment == HolizontalAlignment::Left) return rect.xMin;

	int textWidth = 0;
	if (mResource)
	{
		textWidth = GetDrawStringWidthToHandle(mDisplayText.c_str(), mDisplayText.length(), mResource->GetHandle());
	}
	else
	{
		textWidth = GetDrawStringWidth(mDisplayText.c_str(), mDisplayText.length());
	}

	switch (mHolizontalAlignment)
	{
	case HolizontalAlignment::Center:	return rect.xMin + (rect.width - textWidth) * 0.5f;
	case HolizontalAlignment::Right:		return rect.xMin + rect.width - textWidth;
	}

	return 0;
}

int TextRenderer::CalculateStartPosY(const Rect& rect) const
{
	if (mVerticalAlignment == VerticalAlignment::Top) return rect.yMin;

	int textHeight = 0;
	if (mResource)
	{
		textHeight = GetFontLineSpaceToHandle(mResource->GetHandle());
	}
	else
	{
		textHeight = GetFontLineSpace();
	}

	switch (mVerticalAlignment)
	{
	case VerticalAlignment::Middle:	return rect.yMin + (rect.height - textHeight) * 0.5f;
	case VerticalAlignment::Bottom:	return rect.yMin + rect.height - textHeight;
	}

	return 0;
}
