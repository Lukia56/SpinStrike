#include "UIObject.h"
#include "World/Component/RectTransform.h"

namespace UI
{
	UIObject::UIObject() :
		GameObject(std::make_unique<RectTransform>(this)),
		mRectTransform(nullptr)
	{
		// Transformの二重生成を防ぐためにコンストラクタで生成して、アップキャストしたものを取得する
		mRectTransform = dynamic_cast<RectTransform*>(mTransform.get());
	}
}
