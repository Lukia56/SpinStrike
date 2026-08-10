#include "UIImage.h"
#include <memory>
#include <string>
#include "../Component/Rendering/SpriteRenderer.h"

UIImage::UIImage(const std::string& spritePath) :
	mRenderer(nullptr)
{
	mRenderer = std::make_unique<SpriteRenderer>(this);
	mRenderer->Load(spritePath);
}

void UIImage::Init()
{
}

void UIImage::Update()
{
}

void UIImage::Draw()
{
	mRenderer->Draw();
}
