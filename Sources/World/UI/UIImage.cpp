#include "UIImage.h"
#include <memory>
#include <string>
#include "../Component/RectTransform.h"
#include "../Component/Rendering/UIImageRenderer.h"

namespace UI
{
	Image::Image(const std::string& texturePath) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<UIImageRenderer>(this, mRectTransform);
		mRenderer->Load(texturePath);

		mRectTransform->SetFullRectAsFixed(mRenderer->GetTexSize());
	}

	void Image::Init()
	{
	}

	void Image::Update()
	{
	}

	void Image::Draw()
	{
		mRenderer->Draw();
	}
}
