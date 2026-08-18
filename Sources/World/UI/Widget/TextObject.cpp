#include "TextObject.h"
#include <memory>
#include <string>
#include "World/Component/RectTransform.h"
#include "World/Component/Rendering/TextAlignment.h"
#include "World/Component/Rendering/TextRenderer.h"
#include "Utility/Color.h"

namespace UI
{
	TextObject::TextObject(const std::string& fontPath, const std::string& displayText, const Color& color, HolizontalAlignment hAlign, VerticalAlignment vAlign) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<TextRenderer>(this, mRectTransform, displayText, color, hAlign, vAlign);
		mRenderer->Load(fontPath);
	}

	void TextObject::Init()
	{
	}

	void TextObject::Update()
	{
	}

	void TextObject::Draw()
	{
		mRenderer->Draw();
	}

	void TextObject::SetDisplayText(const std::string& displayText)
	{
		mRenderer->SetDisplayText(displayText);
	}

	void TextObject::SetColor(const Color& color)
	{
		mRenderer->SetColor(color);
	}

	void TextObject::SetHolizontalAlignment(HolizontalAlignment alignment)
	{
		mRenderer->SetHolizontalAlignment(alignment);
	}

	void TextObject::SetVerticalAlignment(VerticalAlignment alignment)
	{
		mRenderer->SetVerticalAlignment(alignment);
	}
}
