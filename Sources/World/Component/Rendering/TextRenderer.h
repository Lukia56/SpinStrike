#pragma once

#include "Renderer.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"

namespace Resource
{
	class Font;
}

/// <summary>
/// テキストの描画を行う
/// </summary>
class TextRenderer : public Renderer<Resource::Font>
{
public:

	TextRenderer(GameObject* owner);
	~TextRenderer() = default;

	/// <summary>
	/// テキストをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

	void SetDisplayText(const std::string& text) { mDisplayText = text; }
	
	void SetColor(const Color& color) { mColor = color; }

	void SetScalingFlag(const bool flag) { mIsScaling = flag; }

private:

	std::string mDisplayText;

	Color mColor;

	bool mIsScaling;
};
