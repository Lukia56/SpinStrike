#include "TextObject.h"
#include <memory>
#include <string>
#include "System/Resource/ResourceBase.h"
#include "Utility/Color.h"
#include "World/Component/Rendering/TextAlignment.h"
#include "World/Component/Rendering/TextRenderer.h"

namespace UI
{
	TextObject::TextObject(std::shared_ptr<Resource::ResourceBase> font, const std::string& displayText, const Color& color, HolizontalAlignment hAlign, VerticalAlignment vAlign) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<TextRenderer>(this, font, mRectTransform, displayText, color, hAlign, vAlign);
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
