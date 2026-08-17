#pragma once

#include "MenuScreen.h"

namespace UI
{
	class TestMenuScreen : public MenuScreen
	{
	public:

		TestMenuScreen();
		~TestMenuScreen() = default;

		void Init() override;
		void Update() override;

		void Setup() override;

		bool ProcessInput(const Input::UIInputState&);
	};
}
