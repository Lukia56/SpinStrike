#pragma once

#include "InputFormatBase.h"

class InputFormatGamepadThumb : public InputFormatBase
{
public:

	InputFormatGamepadThumb() = default;
	~InputFormatGamepadThumb() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector3 GetValue(const KeyCode::Button keyCode) override;
};
