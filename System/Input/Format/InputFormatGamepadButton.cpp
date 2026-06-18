#include "InputFormatGamepadButton.h"
#include <DxLib.h>
#include "../Gamepad.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

void InputFormatGamepadButton::Init()
{
	RegisterKeyCode(KeyCode::Button::GpFaceUp,			XINPUT_BUTTON_Y);
	RegisterKeyCode(KeyCode::Button::GpFaceDown,		XINPUT_BUTTON_A);
	RegisterKeyCode(KeyCode::Button::GpFaceLeft,		XINPUT_BUTTON_X);
	RegisterKeyCode(KeyCode::Button::GpFaceRight,		XINPUT_BUTTON_B);
	RegisterKeyCode(KeyCode::Button::GpDPadUp,			XINPUT_BUTTON_DPAD_UP);
	RegisterKeyCode(KeyCode::Button::GpDPadDown,		XINPUT_BUTTON_DPAD_DOWN);
	RegisterKeyCode(KeyCode::Button::GpDPadLeft,		XINPUT_BUTTON_DPAD_LEFT);
	RegisterKeyCode(KeyCode::Button::GpDPadRight,		XINPUT_BUTTON_DPAD_RIGHT);
	RegisterKeyCode(KeyCode::Button::GpStart,			XINPUT_BUTTON_START);
	RegisterKeyCode(KeyCode::Button::GpBack,			XINPUT_BUTTON_BACK);
	RegisterKeyCode(KeyCode::Button::GpLeftShoulder,	XINPUT_BUTTON_LEFT_SHOULDER);
	RegisterKeyCode(KeyCode::Button::GpRightShoulder,	XINPUT_BUTTON_RIGHT_SHOULDER);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbPress,	XINPUT_BUTTON_LEFT_THUMB);
	RegisterKeyCode(KeyCode::Button::GpRightThumbPress,	XINPUT_BUTTON_RIGHT_THUMB);
}

bool InputFormatGamepadButton::CheckButtonState(const KeyCode::Button keyCode)
{
	int linkedKeyCode = GetLinkToKeyCode().at(keyCode);
	bool result = Gamepad::GetInstance().IsDown(linkedKeyCode);
	return result;
}

Vector3 InputFormatGamepadButton::GetValue(const KeyCode::Button keyCode)
{
	return Vector3(static_cast<float>(CheckButtonState(keyCode)), 0.0f, 0.0f);
}
