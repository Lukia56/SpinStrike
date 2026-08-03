#include "InputFormatMouseButton.h"
#include <DxLib.h>
#include "../Mouse.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

void InputFormatMouseButton::Init()
{
	RegisterKeyCode(KeyCode::Button::MbLeftClick, MOUSE_INPUT_LEFT);
	RegisterKeyCode(KeyCode::Button::MbRightClick, MOUSE_INPUT_RIGHT);
	RegisterKeyCode(KeyCode::Button::MbMiddleClick, MOUSE_INPUT_MIDDLE);
	RegisterKeyCode(KeyCode::Button::MbSideBack, MOUSE_INPUT_4);
	RegisterKeyCode(KeyCode::Button::MbSideFront, MOUSE_INPUT_5);
}

bool InputFormatMouseButton::CheckButtonState(const KeyCode::Button keyCode)
{
	int linkedKeyCode = GetLinkToKeyCode().at(keyCode);
	bool result = Mouse::GetInstance().IsDown(linkedKeyCode);
	return result;
}

Vector3 InputFormatMouseButton::GetValue(const KeyCode::Button keyCode)
{
	return Vector3(static_cast<float>(CheckButtonState(keyCode)), 0.0f, 0.0f);
}
