#pragma once

#include "InputFormatBase.h"

/// <summary>
/// キーボードの入力を取得する
/// </summary>
class InputFormatKeyboard : public InputFormatBase
{
public:

	InputFormatKeyboard() = default;
	~InputFormatKeyboard() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};

