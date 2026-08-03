#include "InputFormatGamepadTrigger.h"
#include <DxLib.h>
#include "../Gamepad.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	float kDeadzoneMin = 0.125f;
	float kDeadzoneMax = 0.925f;
}

void InputFormatGamepadTrigger::Init()
{
	RegisterKeyCode(KeyCode::Button::GpLeftTrigger,		0);
	RegisterKeyCode(KeyCode::Button::GpRightTrigger,	1);
}

bool InputFormatGamepadTrigger::CheckButtonState(const KeyCode::Button keyCode)
{ 
	switch (keyCode)
	{
	case KeyCode::Button::GpLeftTrigger:	return Math::Filter1D(Gamepad::GetInstance().GetState().LeftTrigger, 255, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpRightTrigger:	return Math::Filter1D(Gamepad::GetInstance().GetState().RightTrigger, 255, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	}
	
	return false;
}

Vector3 InputFormatGamepadTrigger::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::GpLeftTrigger:	return Vector3(Math::Filter1D(Gamepad::GetInstance().GetState().LeftTrigger, 255, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpRightTrigger:	return Vector3(Math::Filter1D(Gamepad::GetInstance().GetState().RightTrigger, 255, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	}

	return Vector3::Zero;
}
