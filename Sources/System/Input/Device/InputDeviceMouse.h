#pragma once

#include "InputDeviceBase.h"

/// <summary>
/// マウスの入力フォーマットを管理する
/// </summary>
class InputDeviceMouse :  public InputDeviceBase
{
public:

	InputDeviceMouse() = default;
	~InputDeviceMouse() = default;

protected:

	void InitDevice() override;
};
