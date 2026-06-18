#include "InputDeviceKeyboard.h"
#include "../Format/InputFormatKeyboard.h"

void InputDeviceKeyboard::InitDevice()
{
	RegisterFormat<InputFormatKeyboard>();
}
