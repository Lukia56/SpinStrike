#pragma once

#include "MenuScreen.h"

namespace UI
{
	class TestOptionScreen : public MenuScreen
	{
	public:

		TestOptionScreen();
		~TestOptionScreen() = default;

		void Init() override;
		void Update() override;
		void Draw() override;

		void Setup() override;

		bool ProcessInput(const Input::UIInputState& input);
	};
}
