#include "InputFormatMouseWheel.h"
#include "../Mouse.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

void InputFormatMouseWheel::Init()
{
	RegisterKeyCode(KeyCode::Button::MbWheelUp, 0);
	RegisterKeyCode(KeyCode::Button::MbWheelDown, 1);
	RegisterKeyCode(KeyCode::Button::MbWheelLeft, 2);
	RegisterKeyCode(KeyCode::Button::MbWheelRight, 3);
	RegisterKeyCode(KeyCode::Button::MbWheel, 4);
}

bool InputFormatMouseWheel::CheckButtonState(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbWheelUp:		return Mouse::GetInstance().GetWheelRot().y > 0.0f;
	case KeyCode::Button::MbWheelDown:		return Mouse::GetInstance().GetWheelRot().y < 0.0f;
	case KeyCode::Button::MbWheelLeft:		return Mouse::GetInstance().GetWheelRot().x < 0.0f;
	case KeyCode::Button::MbWheelRight:		return Mouse::GetInstance().GetWheelRot().x > 0.0f;
	case KeyCode::Button::MbWheel:			return Mouse::GetInstance().GetWheelRot() != Vector2::Zero;
	}

	return false;
}

Vector3 InputFormatMouseWheel::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbWheelUp:		return Vector3(Math::Max(Mouse::GetInstance().GetWheelRot().y, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbWheelDown:		return Vector3(Math::Min(Mouse::GetInstance().GetWheelRot().y, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbWheelLeft:		return Vector3(Math::Min(Mouse::GetInstance().GetWheelRot().x, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbWheelRight:		return Vector3(Math::Max(Mouse::GetInstance().GetWheelRot().x, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbWheel:
		Vector2 rot = Mouse::GetInstance().GetWheelRot();
		return Vector3(rot.x, rot.y, 0.0f);
	}

	return Vector3::Zero;
}
