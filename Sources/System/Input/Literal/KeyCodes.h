#pragma once

namespace KeyCode
{
	/// <summary>
	/// デジタル入力を行うボタン
	/// 仮想キーコードを持たないボタンも、同じように処理を行うために自作キーコードとして使う
	/// </summary>
	enum class Button
	{
		None,
		BackSpace,
		Tab,
		Enter,
		NumpadEnter,
		Shift,
		Control,
		Alt,
		PauseBreak,
		CapsLock,
		Escape,
		Space,
		PageUp,
		PageDown,
		End,
		Home,
		LeftArrow,
		UpArrow,
		RightArrow,
		DownArrow,
		Insert,
		Delete,
		Zero,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		Multiply,
		Add,
		Subtract,
		Decimal,
		Divide,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		NumLock,
		ScrollLock,
		LShift,
		RShift,
		LControl,
		RControl,
		LAlt,
		RAlt,
		Colon,
		Semicolon,
		Comma,
		Minus,
		Period,
		Slash,
		At,
		LBracket,
		Yen,
		RBracket,
		Hat,
		BackSlash,

		MbLeftClick,
		MbRightClick,
		MbMiddleClick,
		MbSideBack,
		MbSideFront,
		MbDeltaUp,		// float
		MbDeltaDown,	// float
		MbDeltaLeft,	// float
		MbDeltaRight,	// float
		MbWheelUp,		// float
		MbWheelDown,	// float
		MbWheelLeft,	// float
		MbWheelRight,	// float
		MbDelta,		// Vector2
		MbWheel,		// Vector2

		GpFaceUp,
		GpFaceDown,
		GpFaceLeft,
		GpFaceRight,
		GpDPadUp,
		GpDPadDown,
		GpDPadLeft,
		GpDPadRight,
		GpStart,
		GpBack,
		GpLeftShoulder,
		GpRightShoulder,
		GpLeftThumbPress,
		GpRightThumbPress,
		GpLeftThumbUp,		// float
		GpLeftThumbDown,	// float
		GpLeftThumbLeft,	// float
		GpLeftThumbRight,	// float
		GpRightThumbUp,		// float
		GpRightThumbDown,	// float
		GpRightThumbLeft,	// float
		GpRightThumbRight,	// float
		GpLeftTrigger,		// float
		GpRightTrigger,		// float
		GpLeftThumb,		// Vector2
		GpRightThumb,		// Vector2
	};
}
