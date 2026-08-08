#pragma once

#include <memory>
#include <unordered_map>
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

class InputFormatBase;

template <class T>
concept InputFormat = std::derived_from<T, InputFormatBase>;

/// <summary>
/// フォーマットを管理して、入力状態を計算する基底
/// </summary>
class InputDeviceBase
{
public:

	InputDeviceBase();
	virtual ~InputDeviceBase();

	void Init();

	void Update();

	/// <summary>
	/// 押されたかどうか
	/// </summary>
	bool IsDown(KeyCode::Button keyCode) const;

	/// <summary>
	/// 押された瞬間かどうか
	/// </summary>
	bool IsPressed(KeyCode::Button keyCode) const;

	/// <summary>
	/// 離された瞬間かどうか
	/// </summary>
	bool IsReleased(KeyCode::Button keyCode) const;

	/// <summary>
	/// 一定時間押されているか
	/// </summary>
	/// <param name="frame">押した判定にする閾値</param>
	bool IsHeld(KeyCode::Button keyCode, int frame) const;

	/// <summary>
	/// アナログ値を取得する
	/// </summary>
	Vector3 GetValue(KeyCode::Button keyCode) const;

protected:

	virtual void InitDevice() = 0;

	template <InputFormat T>
	void RegisterFormat();

private:

	void UpdatePressedFrame(InputFormatBase* format, KeyCode::Button keyCode);

private:

	/// <summary>
	/// 押下時間のログ
	/// "+" = 押しているフレーム数
	/// "-" = 離されているフレーム数
	/// </summary>
	std::unordered_map<KeyCode::Button, int> mPressedFrameLogs;

	std::vector<std::unique_ptr<InputFormatBase>> mFormats;
};

template<InputFormat T>
inline void InputDeviceBase::RegisterFormat()
{
	std::unique_ptr<T> format = std::make_unique<T>();
	format->Init();
	mFormats.emplace_back(std::move(format));
}
