#pragma once

#include "InputDeviceBase.h"

class InputDeviceGamepad : public InputDeviceBase
{
public:

	InputDeviceGamepad() = default;
	~InputDeviceGamepad() = default;

protected:

	void InitDevice() override;
};
