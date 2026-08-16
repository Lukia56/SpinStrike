#include "TestScreen.h"
#include "ImageObject.h"
#include "TextObject.h"
#include "../Component/RectTransform.h"

namespace
{
	const char* const kTexturePath = "Resources\\Sprite\\Grass.png";
	const char* const kFontPath = "Resources\\Font\\JFDotK12.dft";
}

UI::TestScreen::TestScreen()
{
	auto image = CreateToChild<UI::ImageObject>(kTexturePath);
	//image->GetRectTransform()->SetPivot(Vector2::Zero);

	auto text = CreateToChild<UI::TextObject>(kFontPath, "Regular Text");
	text->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
}
