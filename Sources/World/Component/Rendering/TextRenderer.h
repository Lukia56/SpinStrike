#pragma once

#include "Renderer.h"
#include "TextAlignment.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"
#include "Utility/Rect.h"

class RectTransform;
namespace Resource
{
	class Font;
}

/// <summary>
/// テキストの描画を行う
/// 配置を変えたときの複数行は未想定
/// </summary>
class TextRenderer : public Renderer<Resource::Font>
{
public:

	TextRenderer(GameObject* owner, RectTransform* rectTransform, const std::string& displayText = "", const Color& color = Color::white,
		HolizontalAlignment hAlign = HolizontalAlignment::Left, VerticalAlignment vAlign = VerticalAlignment::Top);
	~TextRenderer() = default;

	/// <summary>
	/// テキストをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

public:

	void SetDisplayText(const std::string& text) { mDisplayText = text; }
	
	void SetColor(const Color& color) { mColor = color; }

	void SetHolizontalAlignment(HolizontalAlignment alignment) { mHolizontalAlignment = alignment; }
	void SetVerticalAlignment(VerticalAlignment alignment) { mVerticalAlignment = alignment; }

private:

	int CalculateStartPosX(const Rect& rect) const;
	int CalculateStartPosY(const Rect& rect) const;

private:

	std::string mDisplayText;

	Color mColor;

	HolizontalAlignment mHolizontalAlignment;

	VerticalAlignment mVerticalAlignment;

	RectTransform* mRectTransform;
};
