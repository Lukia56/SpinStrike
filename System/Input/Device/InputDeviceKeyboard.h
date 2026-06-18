#pragma once

#include "InputDeviceBase.h"

class InputDeviceKeyboard : public InputDeviceBase
{
public:

	InputDeviceKeyboard() = default;
	~InputDeviceKeyboard() = default;

protected:

	void InitDevice() override;
};
