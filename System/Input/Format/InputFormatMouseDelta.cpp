#include "InputFormatMouseDelta.h"
#include <cmath>
#include "../Mouse.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

void InputFormatMouseDelta::Init()
{
	RegisterKeyCode(KeyCode::Button::MbDeltaUp, 0);
	RegisterKeyCode(KeyCode::Button::MbDeltaDown, 1);
	RegisterKeyCode(KeyCode::Button::MbDeltaLeft, 2);
	RegisterKeyCode(KeyCode::Button::MbDeltaRight, 3);
	RegisterKeyCode(KeyCode::Button::MbDelta, 4);
}

bool InputFormatMouseDelta::CheckButtonState(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbDeltaUp:		return Mouse::GetInstance().GetRelative().y < 0.0f;
	case KeyCode::Button::MbDeltaDown:		return Mouse::GetInstance().GetRelative().y > 0.0f;
	case KeyCode::Button::MbDeltaLeft:		return Mouse::GetInstance().GetRelative().x < 0.0f;
	case KeyCode::Button::MbDeltaRight:		return Mouse::GetInstance().GetRelative().x > 0.0f;
	case KeyCode::Button::MbDelta:			return Mouse::GetInstance().GetRelative() != Vector2::Zero;
	}

	return false;
}

Vector3 InputFormatMouseDelta::GetValue(const KeyCode::Button keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Button::MbDeltaUp:		return Vector3(Math::Min(Mouse::GetInstance().GetRelative().y, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbDeltaDown:		return Vector3(Math::Max(Mouse::GetInstance().GetRelative().y, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbDeltaLeft:		return Vector3(Math::Min(Mouse::GetInstance().GetRelative().x, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbDeltaRight:		return Vector3(Math::Max(Mouse::GetInstance().GetRelative().x, 0.0f), 0.0f, 0.0f);
	case KeyCode::Button::MbDelta:
		Vector2 delta = Mouse::GetInstance().GetRelative();
		return Vector3(delta.x, delta.y, 0.0f);
	}

	return Vector3::Zero;
}
