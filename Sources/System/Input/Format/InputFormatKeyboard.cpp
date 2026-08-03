#include "InputFormatKeyboard.h"
#include <DxLib.h>
#include "../Keyboard.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

void InputFormatKeyboard::Init()
{
	RegisterKeyCode(KeyCode::Button::BackSpace,		KEY_INPUT_BACK);
	RegisterKeyCode(KeyCode::Button::Tab,			KEY_INPUT_TAB);

	RegisterKeyCode(KeyCode::Button::Enter,			KEY_INPUT_RETURN);
	RegisterKeyCode(KeyCode::Button::NumpadEnter,	KEY_INPUT_NUMPADENTER);
	RegisterKeyCode(KeyCode::Button::Shift,			KEY_INPUT_LSHIFT);		// DxLibでの左右Shift対応がうまく出来なかったため左のみ
	RegisterKeyCode(KeyCode::Button::Control,		KEY_INPUT_LCONTROL);	// DxLibでの左右Ctrl対応がうまく出来なかったため左のみ
	RegisterKeyCode(KeyCode::Button::Alt,			KEY_INPUT_LALT);		// DxLibでの左右Alt対応がうまく出来なかったため左のみ
	RegisterKeyCode(KeyCode::Button::PauseBreak,	KEY_INPUT_PAUSE);
	RegisterKeyCode(KeyCode::Button::CapsLock,		KEY_INPUT_CAPSLOCK);

	RegisterKeyCode(KeyCode::Button::Escape,		KEY_INPUT_ESCAPE);

	RegisterKeyCode(KeyCode::Button::Space,			KEY_INPUT_SPACE);
	RegisterKeyCode(KeyCode::Button::PageUp,		KEY_INPUT_PGUP);
	RegisterKeyCode(KeyCode::Button::PageDown,		KEY_INPUT_PGDN);
	RegisterKeyCode(KeyCode::Button::End,			KEY_INPUT_END);
	RegisterKeyCode(KeyCode::Button::Home,			KEY_INPUT_HOME);
	RegisterKeyCode(KeyCode::Button::LeftArrow,		KEY_INPUT_LEFT);
	RegisterKeyCode(KeyCode::Button::UpArrow,		KEY_INPUT_UP);
	RegisterKeyCode(KeyCode::Button::RightArrow,	KEY_INPUT_RIGHT);
	RegisterKeyCode(KeyCode::Button::DownArrow,		KEY_INPUT_DOWN);

	RegisterKeyCode(KeyCode::Button::Insert,		KEY_INPUT_INSERT);
	RegisterKeyCode(KeyCode::Button::Delete,		KEY_INPUT_DELETE);

	RegisterKeyCode(KeyCode::Button::Zero,			KEY_INPUT_0);
	RegisterKeyCode(KeyCode::Button::One,			KEY_INPUT_1);
	RegisterKeyCode(KeyCode::Button::Two,			KEY_INPUT_2);
	RegisterKeyCode(KeyCode::Button::Three,			KEY_INPUT_3);
	RegisterKeyCode(KeyCode::Button::Four,			KEY_INPUT_4);
	RegisterKeyCode(KeyCode::Button::Five,			KEY_INPUT_5);
	RegisterKeyCode(KeyCode::Button::Six,			KEY_INPUT_6);
	RegisterKeyCode(KeyCode::Button::Seven,			KEY_INPUT_7);
	RegisterKeyCode(KeyCode::Button::Eight,			KEY_INPUT_8);
	RegisterKeyCode(KeyCode::Button::Nine,			KEY_INPUT_9);

	RegisterKeyCode(KeyCode::Button::A,				KEY_INPUT_A);
	RegisterKeyCode(KeyCode::Button::B,				KEY_INPUT_B);
	RegisterKeyCode(KeyCode::Button::C,				KEY_INPUT_C);
	RegisterKeyCode(KeyCode::Button::D,				KEY_INPUT_D);
	RegisterKeyCode(KeyCode::Button::E,				KEY_INPUT_E);
	RegisterKeyCode(KeyCode::Button::F,				KEY_INPUT_F);
	RegisterKeyCode(KeyCode::Button::G,				KEY_INPUT_G);
	RegisterKeyCode(KeyCode::Button::H,				KEY_INPUT_H);
	RegisterKeyCode(KeyCode::Button::I,				KEY_INPUT_I);
	RegisterKeyCode(KeyCode::Button::J,				KEY_INPUT_J);
	RegisterKeyCode(KeyCode::Button::K,				KEY_INPUT_K);
	RegisterKeyCode(KeyCode::Button::L,				KEY_INPUT_L);
	RegisterKeyCode(KeyCode::Button::M,				KEY_INPUT_M);
	RegisterKeyCode(KeyCode::Button::N,				KEY_INPUT_N);
	RegisterKeyCode(KeyCode::Button::O,				KEY_INPUT_O);
	RegisterKeyCode(KeyCode::Button::P,				KEY_INPUT_P);
	RegisterKeyCode(KeyCode::Button::Q,				KEY_INPUT_Q);
	RegisterKeyCode(KeyCode::Button::R,				KEY_INPUT_R);
	RegisterKeyCode(KeyCode::Button::S,				KEY_INPUT_S);
	RegisterKeyCode(KeyCode::Button::T,				KEY_INPUT_T);
	RegisterKeyCode(KeyCode::Button::U,				KEY_INPUT_U);
	RegisterKeyCode(KeyCode::Button::V,				KEY_INPUT_V);
	RegisterKeyCode(KeyCode::Button::W,				KEY_INPUT_W);
	RegisterKeyCode(KeyCode::Button::X,				KEY_INPUT_X);
	RegisterKeyCode(KeyCode::Button::Y,				KEY_INPUT_Y);
	RegisterKeyCode(KeyCode::Button::Z,				KEY_INPUT_Z);

	RegisterKeyCode(KeyCode::Button::Numpad0,		KEY_INPUT_NUMPAD0);
	RegisterKeyCode(KeyCode::Button::Numpad1,		KEY_INPUT_NUMPAD1);
	RegisterKeyCode(KeyCode::Button::Numpad2,		KEY_INPUT_NUMPAD2);
	RegisterKeyCode(KeyCode::Button::Numpad3,		KEY_INPUT_NUMPAD3);
	RegisterKeyCode(KeyCode::Button::Numpad4,		KEY_INPUT_NUMPAD4);
	RegisterKeyCode(KeyCode::Button::Numpad5,		KEY_INPUT_NUMPAD5);
	RegisterKeyCode(KeyCode::Button::Numpad6,		KEY_INPUT_NUMPAD6);
	RegisterKeyCode(KeyCode::Button::Numpad7,		KEY_INPUT_NUMPAD7);
	RegisterKeyCode(KeyCode::Button::Numpad8,		KEY_INPUT_NUMPAD8);
	RegisterKeyCode(KeyCode::Button::Numpad9,		KEY_INPUT_NUMPAD9);
	RegisterKeyCode(KeyCode::Button::Multiply,		KEY_INPUT_MULTIPLY);
	RegisterKeyCode(KeyCode::Button::Add,			KEY_INPUT_ADD);
	RegisterKeyCode(KeyCode::Button::Subtract,		KEY_INPUT_SUBTRACT);
	RegisterKeyCode(KeyCode::Button::Decimal,		KEY_INPUT_DECIMAL);
	RegisterKeyCode(KeyCode::Button::Divide,		KEY_INPUT_DIVIDE);
	RegisterKeyCode(KeyCode::Button::F1,			KEY_INPUT_F1);
	RegisterKeyCode(KeyCode::Button::F2,			KEY_INPUT_F2);
	RegisterKeyCode(KeyCode::Button::F3,			KEY_INPUT_F3);
	RegisterKeyCode(KeyCode::Button::F4,			KEY_INPUT_F4);
	RegisterKeyCode(KeyCode::Button::F5,			KEY_INPUT_F5);
	RegisterKeyCode(KeyCode::Button::F6,			KEY_INPUT_F6);
	RegisterKeyCode(KeyCode::Button::F7,			KEY_INPUT_F7);
	RegisterKeyCode(KeyCode::Button::F8,			KEY_INPUT_F8);
	RegisterKeyCode(KeyCode::Button::F9,			KEY_INPUT_F9);
	RegisterKeyCode(KeyCode::Button::F10,			KEY_INPUT_F10);
	RegisterKeyCode(KeyCode::Button::F11,			KEY_INPUT_F11);
	RegisterKeyCode(KeyCode::Button::F12,			KEY_INPUT_F12);

	RegisterKeyCode(KeyCode::Button::NumLock,		KEY_INPUT_NUMLOCK);
	RegisterKeyCode(KeyCode::Button::ScrollLock,	KEY_INPUT_SCROLL);

	RegisterKeyCode(KeyCode::Button::LShift,		KEY_INPUT_LSHIFT);
	RegisterKeyCode(KeyCode::Button::RShift,		KEY_INPUT_RSHIFT);
	RegisterKeyCode(KeyCode::Button::LControl,		KEY_INPUT_LCONTROL);
	RegisterKeyCode(KeyCode::Button::RControl,		KEY_INPUT_RCONTROL);
	RegisterKeyCode(KeyCode::Button::LAlt,			KEY_INPUT_LALT);
	RegisterKeyCode(KeyCode::Button::RAlt,			KEY_INPUT_RALT);

	RegisterKeyCode(KeyCode::Button::Colon,			KEY_INPUT_COLON);
	RegisterKeyCode(KeyCode::Button::Semicolon,		KEY_INPUT_SEMICOLON);
	RegisterKeyCode(KeyCode::Button::Comma,			KEY_INPUT_COMMA);
	RegisterKeyCode(KeyCode::Button::Minus,			KEY_INPUT_MINUS);
	RegisterKeyCode(KeyCode::Button::Period,		KEY_INPUT_PERIOD);
	RegisterKeyCode(KeyCode::Button::Slash,			KEY_INPUT_SLASH);
	RegisterKeyCode(KeyCode::Button::At,			KEY_INPUT_AT);

	RegisterKeyCode(KeyCode::Button::LBracket,		KEY_INPUT_LBRACKET);
	RegisterKeyCode(KeyCode::Button::Yen,			KEY_INPUT_YEN);
	RegisterKeyCode(KeyCode::Button::RBracket,		KEY_INPUT_RBRACKET);
	RegisterKeyCode(KeyCode::Button::Hat,			KEY_INPUT_PREVTRACK);

	RegisterKeyCode(KeyCode::Button::BackSlash,		KEY_INPUT_BACKSLASH);
}

bool InputFormatKeyboard::CheckButtonState(const KeyCode::Button keyCode)
{
	int linkedKeyCode = GetLinkToKeyCode().at(keyCode);
	bool result = Keyboard::GetInstance().IsDown(linkedKeyCode);
	return result;
}

Vector3 InputFormatKeyboard::GetValue(const KeyCode::Button keyCode)
{
	return Vector3(static_cast<float>(CheckButtonState(keyCode)), 0.0f, 0.0f);
}
