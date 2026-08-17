#pragma once

#include "UIObject.h"

namespace UI
{
	/// <summary>
	/// UI用のルート用オブジェクト
	/// </summary>
	class UIRoot : public UIObject
	{
	public:

		UIRoot() = default;
		~UIRoot() = default;

		void Init() override {};
		void Update() override {};
	};
}
