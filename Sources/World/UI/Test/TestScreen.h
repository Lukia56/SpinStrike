#pragma once

#include "../Core/Screen.h"

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
