#include "BoxObject.h"
#include <DxLib.h>

namespace UI
{
	BoxObject::BoxObject(const Color& color) :
		mColor(color)
	{
	}

	void BoxObject::Init()
	{
	}

	void BoxObject::Update()
	{
	}

	void BoxObject::Draw()
	{
		Rect rect = mRectTransform->CalculateRect();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mColor.a * 255);

		DrawBox(rect.xMin, rect.yMin, rect.xMin + rect.width, rect.yMin + rect.height, mColor.GetAsHexRGB(), true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
