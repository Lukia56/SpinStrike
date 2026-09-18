#include "ImageObject.h"
#include <memory>
#include "System/Resource/ResourceBase.h"
#include "World/Component/RectTransform.h"
#include "World/Component/Rendering/UIImageRenderer.h"

namespace UI
{
	ImageObject::ImageObject(std::shared_ptr<Resource::ResourceBase> texture) :
		mRenderer(nullptr)
	{
		mRenderer = std::make_unique<UIImageRenderer>(this, texture, mRectTransform);

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
