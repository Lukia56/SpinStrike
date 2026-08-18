#pragma once

#include "../Core/UIObject.h"
#include <string>
#include "Utility/Color.h"
#include "World/Component/Rendering/TextAlignment.h"

class TextRenderer;

namespace UI
{
	/// <summary>
	/// 矩形の左上にUIテキストを表示する
	/// 矩形は自分で設定する必要がある
	/// </summary>
	class TextObject : public UIObject
	{
	public:

		TextObject(const std::string& fontPath, const std::string& displayText, const Color& color = Color::white,
			HolizontalAlignment hAlign = HolizontalAlignment::Left, VerticalAlignment vAlign = VerticalAlignment::Top);
		~TextObject() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	public:

		void SetDisplayText(const std::string& displayText);
		void SetColor(const Color& color);
		void SetHolizontalAlignment(HolizontalAlignment alignment);
		void SetVerticalAlignment(VerticalAlignment alignment);

	private:

		std::unique_ptr<TextRenderer> mRenderer;
	};
}
