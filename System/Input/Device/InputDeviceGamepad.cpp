#include "InputDeviceGamepad.h"
#include "../Format/InputFormatGamepadButton.h"
#include "../Format/InputFormatGamepadThumb.h"
#include "../Format/InputFormatGamepadTrigger.h"

void InputDeviceGamepad::InitDevice()
{
	RegisterFormat<InputFormatGamepadButton>();
	RegisterFormat<InputFormatGamepadThumb>();
	RegisterFormat<InputFormatGamepadTrigger>();
}
