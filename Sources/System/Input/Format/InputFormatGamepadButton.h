#pragma once

#include "InputFormatBase.h"

/// <summary>
/// ゲームパッドのボタン入力を取得する
/// </summary>
class InputFormatGamepadButton : public InputFormatBase
{
public:

	InputFormatGamepadButton() = default;
	~InputFormatGamepadButton() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
