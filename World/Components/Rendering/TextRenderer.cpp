#include "TextRenderer.h"
#include <DxLib.h>
#include "../../GameObject.h"
#include "System/Resource/Resource.h"
#include "Utility/Color.h"

TextRenderer::TextRenderer(GameObject* owner) :
	Renderer(owner),
	mDisplayText(""),
	mColor(Color::white),
	mIsScaling(false)
{
}

void TextRenderer::Draw()
{
	if (!mOwner) return;

	const VECTOR pos = mOwner->GetTransform().CalculateWorldPosition().GetAsDxLibVector();
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);

	// 必要な場合のみワールドスケールを計算して取得
	if (mIsScaling)
	{
		scale = mOwner->GetTransform().CalculateWorldScale().GetAsDxLibVector();
	}

	// フォントが読み込まれていたらフォントを使用してテキストを表示する
	if (mResource)
	{
		if (mIsScaling)
			DrawExtendStringFToHandle(pos.x, pos.y, scale.x, scale.y, mDisplayText.c_str(), mColor.GetAsHexRGB(), mResource->GetHandle());
		else
			DrawStringFToHandle(pos.x, pos.y, mDisplayText.c_str(), mColor.GetAsHexRGB(), mResource->GetHandle());
	}
	// フォントが読み込まれていなかったらデフォルトのフォントを使用してテキストを表示する
	else
	{
		if (mIsScaling)
			DrawExtendStringF(pos.x, pos.y, scale.x, scale.y, mDisplayText.c_str(), mColor.GetAsHexRGB());
		else
			DrawStringF(pos.x, pos.y, mDisplayText.c_str(), mColor.GetAsHexRGB());
	}
}
