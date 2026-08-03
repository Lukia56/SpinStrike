#pragma once

#include "InputFormatBase.h"

class InputFormatMouseButton : public InputFormatBase
{
public:

	InputFormatMouseButton() = default;
	~InputFormatMouseButton() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector3 GetValue(const KeyCode::Button keyCode) override;
};
