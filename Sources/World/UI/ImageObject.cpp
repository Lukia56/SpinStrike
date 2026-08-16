#include "ImageObject.h"
#include <memory>
#include <string>
#include "../Component/RectTransform.h"
#include "../Component/Rendering/UIImageRenderer.h"

namespace UI
{
	ImageObject::ImageObject(const std::string& texturePath) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<UIImageRenderer>(this, mRectTransform);
		mRenderer->Load(texturePath);

		SetRectSizeToTexSize();
	}

	void ImageObject::Init()
	{
	}

	void ImageObject::Update()
	{
	}

	void ImageObject::Draw()
	{
		mRenderer->Draw();
	}

	void ImageObject::SetRectSizeToTexSize()
	{
		mRectTransform->SetFullRectAsFixed(mRenderer->GetTexSize());
	}
}
