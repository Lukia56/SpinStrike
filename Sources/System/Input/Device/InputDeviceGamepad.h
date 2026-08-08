#pragma once

#include "InputDeviceBase.h"

/// <summary>
/// ゲームパッドの入力フォーマットを管理する
/// </summary>
class InputDeviceGamepad : public InputDeviceBase
{
public:

	InputDeviceGamepad() = default;
	~InputDeviceGamepad() = default;

protected:

	void InitDevice() override;
};
