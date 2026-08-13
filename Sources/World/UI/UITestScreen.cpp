#include "UITestScreen.h"
#include "UIImage.h"
#include "UIText.h"
#include "../Component/RectTransform.h"

namespace
{
	const char* const kTexturePath = "Resources\\Sprite\\Grass.png";
	const char* const kFontPath = "Resources\\Font\\JFDotK12.dft";
}

UI::TestScreen::TestScreen()
{
	auto image = CreateToChild<UI::Image>(kTexturePath);
	//image->GetRectTransform()->SetPivot(Vector2::Zero);

	auto text = CreateToChild<UI::Text>(kFontPath, "Regular Text");
	text->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
}
