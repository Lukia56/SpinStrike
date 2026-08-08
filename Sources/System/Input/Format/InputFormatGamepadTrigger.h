#pragma once

#include "InputFormatBase.h"

/// <summary>
/// ゲームパッドのトリガーボタン入力を取得する
/// </summary>
class InputFormatGamepadTrigger : public InputFormatBase
{
public:

	InputFormatGamepadTrigger() = default;
	~InputFormatGamepadTrigger() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
