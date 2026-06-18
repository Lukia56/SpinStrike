#pragma once

#include "InputFormatBase.h"

class InputFormatMouseDelta : public InputFormatBase
{
public:

	InputFormatMouseDelta() = default;
	~InputFormatMouseDelta() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) override;

	Vector3 GetValue(const KeyCode::Button keyCode) override;
};
