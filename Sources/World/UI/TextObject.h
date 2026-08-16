#pragma once

#include "UIObject.h"
#include <string>
#include "Utility/Color.h"

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

		TextObject(const std::string& fontPath, const std::string& displayText, const Color& color = Color::white);
		~TextObject() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	public:

		void SetDisplayText(const std::string& displayText);
		void SetColor(const Color& color);

	private:

		std::unique_ptr<TextRenderer> mRenderer;
	};
}
