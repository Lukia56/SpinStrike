#pragma once

#include "InputFormatBase.h"

/// <summary>
/// マウスのホイール入力を取得する
/// </summary>
class InputFormatMouseWheel : public InputFormatBase
{
public:

	InputFormatMouseWheel() = default;
	~InputFormatMouseWheel() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
