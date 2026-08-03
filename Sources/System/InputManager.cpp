#include "InputManager.h"
#include <array>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Input/Gamepad.h"
#include "Input/Device/InputDeviceKeyboard.h"
#include "Input/Device/InputDeviceMouse.h"
#include "Input/Device/InputDeviceGamepad.h"
#include "Input/Literal/InputActions.h"
#include "Input/Literal/InputProperty.h"
#include "Input/Modifier/InputModifierNegate.h"
#include "Input/Modifier/InputModifierSwizzleAxis.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

bool InputManager::Initialize()
{
	RegisterDevice<InputDeviceKeyboard>(Input::Device::Keyboard);
	RegisterDevice<InputDeviceMouse>(Input::Device::Mouse);
	RegisterDevice<InputDeviceGamepad>(Input::Device::Gamepad);

	mActions.fill(Input::ActionProperty());
	mActionMapState.fill(true);

	mActions[static_cast<size_t>(Input::Action::Move)].map = Input::ActionMap::Player;
	mActions[static_cast<size_t>(Input::Action::Look)].map = Input::ActionMap::Player;
	mActions[static_cast<size_t>(Input::Action::Jump)].map = Input::ActionMap::Player;
	mActions[static_cast<size_t>(Input::Action::Dash)].map = Input::ActionMap::Player;
	mActions[static_cast<size_t>(Input::Action::Spin)].map = Input::ActionMap::Player;
	mActions[static_cast<size_t>(Input::Action::Up)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Down)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Left)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Right)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Submit)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Cancel)].map = Input::ActionMap::UI;
	mActions[static_cast<size_t>(Input::Action::Fly)].map = Input::ActionMap::Debug;

	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::W,
		{
			std::make_shared<InputModifierSwizzleAxis>(InputModifierSwizzleAxis::Order::ZYX)
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::S,
		{
			std::make_shared<InputModifierNegate>(true, true, true),
			std::make_shared<InputModifierSwizzleAxis>(InputModifierSwizzleAxis::Order::ZYX)
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::A,
		{
			std::make_shared<InputModifierNegate>(true, true, true)
		});
	Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::D);
	Bind(Input::Action::Move, Input::Device::Gamepad, KeyCode::Button::GpLeftThumb,
		{ std::make_shared<InputModifierSwizzleAxis>(InputModifierSwizzleAxis::Order::XZY) });

	Bind(Input::Action::Look, Input::Device::Mouse, KeyCode::Button::MbDelta,
		{
			std::make_shared<InputModifierNegate>(false, true, false),
			std::make_shared<InputModifierSwizzleAxis>(InputModifierSwizzleAxis::Order::YXZ)
		});
	Bind(Input::Action::Look, Input::Device::Gamepad, KeyCode::Button::GpRightThumb,
		{ std::make_shared<InputModifierSwizzleAxis>(InputModifierSwizzleAxis::Order::YXZ) });

	Bind(Input::Action::Jump, Input::Device::Keyboard, KeyCode::Button::Space);
	Bind(Input::Action::Jump, Input::Device::Gamepad, KeyCode::Button::GpFaceDown);
	Bind(Input::Action::Dash, Input::Device::Keyboard, KeyCode::Button::LShift);
	Bind(Input::Action::Dash, Input::Device::Gamepad, KeyCode::Button::GpFaceLeft);
	Bind(Input::Action::Spin, Input::Device::Mouse, KeyCode::Button::MbRightClick);

	Bind(Input::Action::Up, Input::Device::Keyboard, KeyCode::Button::W);
	Bind(Input::Action::Up, Input::Device::Keyboard, KeyCode::Button::UpArrow);
	Bind(Input::Action::Down, Input::Device::Keyboard, KeyCode::Button::S);
	Bind(Input::Action::Down, Input::Device::Keyboard, KeyCode::Button::DownArrow);
	Bind(Input::Action::Left, Input::Device::Keyboard, KeyCode::Button::A);
	Bind(Input::Action::Left, Input::Device::Keyboard, KeyCode::Button::LeftArrow);
	Bind(Input::Action::Right, Input::Device::Keyboard, KeyCode::Button::D);
	Bind(Input::Action::Right, Input::Device::Keyboard, KeyCode::Button::RightArrow);
	Bind(Input::Action::Up, Input::Device::Gamepad, KeyCode::Button::GpFaceUp);
	Bind(Input::Action::Down, Input::Device::Gamepad, KeyCode::Button::GpFaceDown);
	Bind(Input::Action::Left, Input::Device::Gamepad, KeyCode::Button::GpFaceLeft);
	Bind(Input::Action::Right, Input::Device::Gamepad, KeyCode::Button::GpFaceRight);
	Bind(Input::Action::Submit, Input::Device::Keyboard, KeyCode::Button::Enter);
	Bind(Input::Action::Submit, Input::Device::Keyboard, KeyCode::Button::Z);
	Bind(Input::Action::Submit, Input::Device::Gamepad, KeyCode::Button::GpFaceRight);
	Bind(Input::Action::Cancel, Input::Device::Keyboard, KeyCode::Button::Shift);
	Bind(Input::Action::Cancel, Input::Device::Gamepad, KeyCode::Button::GpFaceDown);

	Bind(Input::Action::Fly, Input::Device::Keyboard, KeyCode::Button::Space);
	Bind(Input::Action::Fly, Input::Device::Keyboard, KeyCode::Button::LShift, { std::make_shared<InputModifierNegate>(true, false, false) });
	Bind(Input::Action::Fly, Input::Device::Gamepad, KeyCode::Button::GpFaceRight);
	Bind(Input::Action::Fly, Input::Device::Gamepad, KeyCode::Button::GpFaceDown, { std::make_shared<InputModifierNegate>(true, false, false) });

	return true;
}

void InputManager::Update()
{
	Keyboard::GetInstance().Update();
	Mouse::GetInstance().Update();
	Gamepad::GetInstance().Update();

	for (const auto& device : mDevices)
	{
		device.second->Update();
	}
}

bool InputManager::IsDown(Input::Action action) const
{
	return GetState(action, InputType::Down);
}

bool InputManager::IsPressed(Input::Action action) const
{
	return GetState(action, InputType::Pressed);
}

bool InputManager::IsReleased(Input::Action action) const
{
	return GetState(action, InputType::Released);
}

bool InputManager::IsHeld(Input::Action action, int frame) const
{
	return GetState(action, InputType::Held, frame);
}

float InputManager::GetAsFloat(Input::Action action) const
{
	Vector3 value = InputManager::GetValue(action);
	return value.x;
}

Vector2 InputManager::GetAsVector2(Input::Action action) const
{
	Vector3 value = InputManager::GetValue(action);
	return Vector2(value.x, value.y);
}

Vector3 InputManager::GetAsVector3(Input::Action action) const
{
	Vector3 value = InputManager::GetValue(action);
	return value;
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;

	return instance;
}

bool InputManager::GetState(Input::Action action, InputType inputType, int frame) const
{
	const Input::ActionProperty actionProperty = mActions[static_cast<size_t>(action)];

	// 対応したアクションマップが無効化されていたらfalse
	if (!mActionMapState[static_cast<size_t>(actionProperty.map)]) return false;

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();

		// 押下状態を取得する
		// 割り当てられたボタンのどれかが押されていたらtrueとする
		switch (inputType)
		{
		case InputType::Down:
			if (device->IsDown(bind.keyCode)) return true;
			break;

		case InputType::Pressed:
			if (device->IsPressed(bind.keyCode)) return true;
			break;

		case InputType::Released:
			if (device->IsReleased(bind.keyCode)) return true;
			break;

		case InputType::Held:
			if (device->IsHeld(bind.keyCode, frame)) return true;
			break;
		}
	}

	// ここまで来たら押されていないためfalse
	return false;
}

Vector3 InputManager::GetValue(Input::Action action) const
{
	const Input::ActionProperty actionProperty = mActions[static_cast<size_t>(action)];

	// 対応したアクションマップが無効化されていたら
	if (!mActionMapState[static_cast<size_t>(actionProperty.map)]) return Vector3::Zero;

	Vector3 result = Vector3::Zero;

	// アクションに割り当てられたボタンをすべてチェックする
	for (const auto& bind : actionProperty.binds)
	{
		auto device = mDevices.at(bind.device).get();

		Vector3 value = device->GetValue(bind.keyCode);

		// バインドに割り当てられた加工をする
		for (const auto& modifier : bind.modifiers)
		{
			modifier->ModifyRaw(value);
		}

		// 絶対値が大きい方を使用する
		if (std::abs(result.x) < std::abs(value.x)) result.x = value.x;
		if (std::abs(result.y) < std::abs(value.y)) result.y = value.y;
		if (std::abs(result.z) < std::abs(value.z)) result.z = value.z;
	}

	if (result.GetSqLength() > 1.0f) result = result.GetNormalize();

	return result;
}

void InputManager::Bind(Input::Action action, Input::Device device, KeyCode::Button button, std::vector<std::shared_ptr<IInputModifier>> modifiers, Input::PadSlot slot)
{
	Input::BindProperty bind;
	bind.device = device;
	bind.keyCode = button;
	bind.modifiers = modifiers;
	bind.slot = slot;
	mActions[static_cast<size_t>(action)].binds.emplace_back(bind);
}
