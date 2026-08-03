#include "InputDeviceMouse.h"
#include "../Format/InputFormatMouseButton.h"
#include "../Format/InputFormatMouseDelta.h"
#include "../Format/InputFormatMouseWheel.h"

void InputDeviceMouse::InitDevice()
{
	RegisterFormat<InputFormatMouseButton>();
	RegisterFormat<InputFormatMouseDelta>();
	RegisterFormat<InputFormatMouseWheel>();
}
