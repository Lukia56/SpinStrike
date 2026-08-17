#pragma once

#include "World/GameObject.h"
#include "World/Component/RectTransform.h"

namespace UI
{
	/// <summary>
	/// RectTransformを持ったUIオブジェクトの基底
	/// </summary>
	class UIObject : public GameObject
	{
	public:

		UIObject();
		virtual ~UIObject() = default;

		RectTransform* GetRectTransform() const { return mRectTransform; }

	protected:

		RectTransform* mRectTransform;
	};
}
