#include "InputFormatGamepadThumb.h"
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

void InputFormatGamepadThumb::Init()
{
	RegisterKeyCode(KeyCode::Button::GpLeftThumbUp,		0);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbDown,	1);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbLeft,	2);
	RegisterKeyCode(KeyCode::Button::GpLeftThumbRight,	3);
	RegisterKeyCode(KeyCode::Button::GpRightThumbUp,	4);
	RegisterKeyCode(KeyCode::Button::GpRightThumbDown,	5);
	RegisterKeyCode(KeyCode::Button::GpRightThumbLeft,	6);
	RegisterKeyCode(KeyCode::Button::GpRightThumbRight,	7);
	RegisterKeyCode(KeyCode::Button::GpLeftThumb,		8);
	RegisterKeyCode(KeyCode::Button::GpRightThumb,		9);
}

bool InputFormatGamepadThumb::CheckButtonState(const KeyCode::Button keyCode)
{
	const XINPUT_STATE& state = Gamepad::GetInstance().GetState();

	switch (keyCode)
	{
	case KeyCode::Button::GpLeftThumbUp:		return Math::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpLeftThumbDown:		return Math::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpLeftThumbLeft:		return Math::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpLeftThumbRight:		return Math::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpRightThumbUp:		return Math::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;
	case KeyCode::Button::GpRightThumbDown:		return Math::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpRightThumbLeft:		return Math::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax) < 0.0f;
	case KeyCode::Button::GpRightThumbRight:	return Math::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax) > 0.0f;

	case KeyCode::Button::GpLeftThumb:			return Math::Filter2D(state.ThumbLX, state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax) != Vector2::Zero;
	case KeyCode::Button::GpRightThumb:			return Math::Filter2D(state.ThumbRX, state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax) != Vector2::Zero;
	}
	
	return false;
}

Vector3 InputFormatGamepadThumb::GetValue(const KeyCode::Button keyCode)
{
	const XINPUT_STATE& state = Gamepad::GetInstance().GetState();

	switch (keyCode)
	{
	case KeyCode::Button::GpLeftThumbUp:		return Vector3(Math::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpLeftThumbDown:		return Vector3(Math::Filter1D(state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpLeftThumbLeft:		return Vector3(Math::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpLeftThumbRight:		return Vector3(Math::Filter1D(state.ThumbLX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpRightThumbUp:		return Vector3(Math::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpRightThumbDown:		return Vector3(Math::Filter1D(state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpRightThumbLeft:		return Vector3(Math::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);
	case KeyCode::Button::GpRightThumbRight:	return Vector3(Math::Filter1D(state.ThumbRX, 32767, kDeadzoneMin, kDeadzoneMax), 0.0f, 0.0f);

	case KeyCode::Button::GpLeftThumb:
	{
		Vector2 filtered = Math::Filter2D(state.ThumbLX, state.ThumbLY, 32767, kDeadzoneMin, kDeadzoneMax);
		return Vector3(filtered.x, filtered.y, 0.0f);
	}
	case KeyCode::Button::GpRightThumb:
	{
		Vector2 filtered = Math::Filter2D(state.ThumbRX, state.ThumbRY, 32767, kDeadzoneMin, kDeadzoneMax);
		return Vector3(filtered.x, filtered.y, 0.0f);
	}
	}

	return Vector3::Zero;
}
