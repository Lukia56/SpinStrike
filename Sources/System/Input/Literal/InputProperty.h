#pragma once

#include <memory>
#include <vector>
#include "KeyCodes.h"
#include "InputActionMaps.h"

class IInputModifier;

namespace Input
{
	// デバイスの種類
	enum class Device
	{
		None,
		Keyboard,
		Mouse,
		Gamepad,
		Length
	};

	// ゲームパッドの識別子
	enum class PadSlot
	{
		Player1,
		Player2,
		Player3,
		Player4,
		Length
	};

	// バインド情報
	struct BindProperty
	{
		// キーコード
		KeyCode::Button keyCode;

		// デバイスの種類
		Device device = Device::Keyboard;

		// 修飾子
		std::vector<std::shared_ptr<IInputModifier>> modifiers;

		// スロット番号（ゲームパッド用、他では無視される）
		PadSlot slot = PadSlot::Player1;
	};

	// アクション情報
	struct ActionProperty
	{
		// バインド
		std::vector<BindProperty> binds;

		ActionMap map;
	};
}
