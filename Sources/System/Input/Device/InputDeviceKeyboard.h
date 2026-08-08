#pragma once

#include "InputDeviceBase.h"

/// <summary>
/// キーボードの入力フォーマットを管理する
/// </summary>
class InputDeviceKeyboard : public InputDeviceBase
{
public:

	InputDeviceKeyboard() = default;
	~InputDeviceKeyboard() = default;

protected:

	void InitDevice() override;
};
