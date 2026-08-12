#include "TextRenderer.h"
#include <DxLib.h>
#include "../RectTransform.h"
#include "../../GameObject.h"
#include "Utility/Color.h"
#include "Utility/Rect.h"

TextRenderer::TextRenderer(GameObject* owner, RectTransform* rectTransform, const std::string& displayText, const Color& color) :
	Renderer(owner),
	mDisplayText(displayText),
	mColor(color),
	mRectTransform(rectTransform)
{
}

void TextRenderer::Draw() const
{
	if (!mOwner) return;

	Rect rect = mRectTransform->CalculateRect();
	rect.xMin += mOffsetPos.x;
	rect.yMin += mOffsetPos.y;
	
	// フォントが読み込まれていたらフォントを使用してテキストを表示する
	if (mResource)
	{
		DrawStringFToHandle(rect.xMin, rect.yMin, mDisplayText.c_str(), mColor.GetAsHexRGB(), mResource->GetHandle());
	}
	// フォントが読み込まれていなかったらデフォルトのフォントを使用してテキストを表示する
	else
	{
		DrawStringF(rect.xMin, rect.yMin, mDisplayText.c_str(), mColor.GetAsHexRGB());
	}
}
