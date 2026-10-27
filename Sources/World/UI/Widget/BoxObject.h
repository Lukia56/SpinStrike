#pragma once

#include "../Core/UIObject.h"
#include "Utility/Color.h"

namespace UI
{
	class BoxObject : public UIObject
	{
	public:

		BoxObject(const Color& color = Color::white);
		~BoxObject() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	public:

		void SetColor(const Color& color) { mColor = color; };

	private:

		Color mColor;
	};
}
