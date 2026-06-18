#pragma once

#include "InputFormatBase.h"

class InputFormatKeyboard : public InputFormatBase
{
public:

	InputFormatKeyboard() = default;
	~InputFormatKeyboard() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector3 GetValue(const KeyCode::Button keyCode) override;
};

