#include "TestScreen.h"
#include "../Widget/ImageObject.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "System/Resource/Texture.h"
#include "World/Component/RectTransform.h"

namespace
{
	const char* const kTexturePath = "Resources\\Sprite\\Grass.png";
	const char* const kFontPath = "Resources\\Font\\JFDotK12.dft";
}

UI::TestScreen::TestScreen()
{
	std::shared_ptr<Resource::ResourceBase> texture = ResourceManager::GetInstance().GetResource<Resource::Texture>(kTexturePath);
	std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

	auto image = CreateToChild<UI::ImageObject>(texture);
	//image->GetRectTransform()->SetPivot(Vector2::Zero);

	auto text = CreateToChild<UI::TextObject>(font, "Regular Text");
	text->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
}
