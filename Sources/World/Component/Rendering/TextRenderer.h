#pragma once

#include "Renderer.h"
#include "Utility/Color.h"

/// <summary>
/// テキストの描画を行う
/// </summary>
class TextRenderer : public Renderer<Font>
{
public:

	TextRenderer(GameObject* owner);
	~TextRenderer() = default;

	/// <summary>
	/// テキストをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() override;

	void SetDisplayText(const std::string& text) { mDisplayText = text; }
	
	void SetColor(const Color& color) { mColor = color; }

	void SetScalingFlag(const bool flag) { mIsScaling = flag; }

private:

	std::string mDisplayText;

	Color mColor;

	bool mIsScaling;
};
