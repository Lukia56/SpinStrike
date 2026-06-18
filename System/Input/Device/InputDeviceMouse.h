#pragma once

#include "InputDeviceBase.h"

class InputDeviceMouse :  public InputDeviceBase
{
public:

	InputDeviceMouse() = default;
	~InputDeviceMouse() = default;

protected:

	void InitDevice() override;
};
