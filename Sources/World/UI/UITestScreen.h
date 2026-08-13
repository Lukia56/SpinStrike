#pragma once

#include "UIScreen.h"

namespace UI
{
	class TestScreen : public Screen
	{
	public:

		TestScreen();
		~TestScreen() = default;

		void Init() override {}
		void Update() override {}
	};
}

