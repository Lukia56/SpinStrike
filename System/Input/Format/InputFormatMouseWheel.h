#pragma once

#include "InputFormatBase.h"

class InputFormatMouseWheel : public InputFormatBase
{
public:

	InputFormatMouseWheel() = default;
	~InputFormatMouseWheel() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector3 GetValue(const KeyCode::Button keyCode) override;
};
