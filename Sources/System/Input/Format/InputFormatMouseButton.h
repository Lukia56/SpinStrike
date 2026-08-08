#pragma once

#include "InputFormatBase.h"

/// <summary>
/// マウスのボタン入力を取得する
/// </summary>
class InputFormatMouseButton : public InputFormatBase
{
public:

	InputFormatMouseButton() = default;
	~InputFormatMouseButton() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
