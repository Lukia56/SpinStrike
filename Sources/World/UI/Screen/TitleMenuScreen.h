#pragma once

#include "MenuScreen.h"

class TitleMenuScreen : public UI::MenuScreen
{
public:

	TitleMenuScreen();
	~TitleMenuScreen() = default;

	void Init() override;
	void Update() override;

	void Setup() override;

	bool ProcessInput(const Input::UIInputState& input);
};
