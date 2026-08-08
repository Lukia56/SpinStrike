#pragma once

#include "InputFormatBase.h"

/// <summary>
/// ゲームパッドのスティック入力を取得する
/// </summary>
class InputFormatGamepadThumb : public InputFormatBase
{
public:

	InputFormatGamepadThumb() = default;
	~InputFormatGamepadThumb() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
