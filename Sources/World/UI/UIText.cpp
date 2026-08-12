#include "UIText.h"
#include <memory>
#include <string>
#include "../Component/RectTransform.h"
#include "../Component/Rendering/TextRenderer.h"
#include "Utility/Color.h"

namespace UI
{
	Text::Text(const std::string& fontPath, const std::string& displayText, const Color& color) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<TextRenderer>(this, mRectTransform, displayText, color);
		mRenderer->Load(fontPath);
	}

	void Text::Init()
	{
	}

	void Text::Update()
	{
	}

	void Text::Draw()
	{
		mRenderer->Draw();
	}

	void Text::SetDisplayText(const std::string& displayText)
	{
		mRenderer->SetDisplayText(displayText);
	}

	void Text::SetColor(const Color& color)
	{
		mRenderer->SetColor(color);
	}
}
