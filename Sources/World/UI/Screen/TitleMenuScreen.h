#pragma once

#include "MenuScreen.h"

namespace UI
{
	class TitleMenuScreen : public MenuScreen
	{
	public:

		TitleMenuScreen();
		~TitleMenuScreen() = default;

		void Init() override;
		void Update() override;

		void Setup() override;

		bool ProcessInput(const Input::UIInputState& input);
	};
}
