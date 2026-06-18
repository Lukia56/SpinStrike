#pragma once

#include <array>
#include <DxLib.h>
#include "Literal/InputProperty.h"

/// <summary>
/// ゲームパッドの入力管理
/// </summary>
class Gamepad
{
public:

	~Gamepad() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうかを取得する
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <param name="slot">ゲームパッドの識別番号</param>
	/// <returns>押下状態</returns>
	bool IsDown(int keyCode, Input::PadSlot slot = Input::PadSlot::Player1) const;

public:

	/// <summary>
	/// 入力状態を取得
	/// </summary>
	/// <param name="slot">ゲームパッドの識別番号</param>
	const XINPUT_STATE& GetState(Input::PadSlot slot = Input::PadSlot::Player1) const { return mState[static_cast<int>(slot)]; }

public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static Gamepad& GetInstance();

private:

	Gamepad();
	// コピーコンストラクタ禁止
	Gamepad(const Gamepad&) = delete;
	// コピー代入禁止
	Gamepad& operator=(const Gamepad&) = delete;
	// ムーブ禁止
	Gamepad(Gamepad&&) = delete;
	// ムーブ代入禁止
	Gamepad& operator=(Gamepad&&) = delete;

	/// <summary>
	/// キーボードの押下状態
	/// </summary>
	std::array<XINPUT_STATE, static_cast<int>(Input::PadSlot::Length)> mState;

	/// <summary>
	/// 接続しているゲームパッドの数
	/// </summary>
	int mConnectedNum;
};

