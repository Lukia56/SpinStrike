#pragma once

#include <array>
#include <DxLib.h>
#include "Literal/InputProperty.h"

/// <summary>
/// ゲームパッドの入力管理をする
/// </summary>
class Gamepad
{
public:

	~Gamepad() = default;

	void Update();

	bool IsDown(int keyCode, Input::PadSlot slot = Input::PadSlot::Player1) const;

public:

	const XINPUT_STATE& GetState(Input::PadSlot slot = Input::PadSlot::Player1) const { return mState[static_cast<int>(slot)]; }

public:

	static Gamepad& GetInstance();

private:

	Gamepad();

	Gamepad(const Gamepad&) = delete;
	Gamepad& operator=(const Gamepad&) = delete;
	Gamepad(Gamepad&&) = delete;
	Gamepad& operator=(Gamepad&&) = delete;

	std::array<XINPUT_STATE, static_cast<int>(Input::PadSlot::Length)> mState;

	int mConnectedNum;
};

