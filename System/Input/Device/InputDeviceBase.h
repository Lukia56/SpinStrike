#pragma once

#include <memory>
#include <unordered_map>
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

class InputFormatBase;

// 入力フォーマットであることを表すコンセプト
template <class T>
concept InputFormat = std::derived_from<T, InputFormatBase>;

/// <summary>
/// フォーマットを管理する入力デバイスのクラス
/// </summary>
class InputDeviceBase
{
public:

	InputDeviceBase();
	virtual ~InputDeviceBase();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 押されたかどうか
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <returns>押下状態</returns>
	bool IsDown(KeyCode::Button keyCode) const;

	/// <summary>
	/// 押された瞬間かどうか
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <returns>押下状態</returns>
	bool IsPressed(KeyCode::Button keyCode) const;

	/// <summary>
	/// 離された瞬間かどうか
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <returns>押下状態</returns>
	bool IsReleased(KeyCode::Button keyCode) const;

	/// <summary>
	/// 一定時間押されているか
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <param name="frame">押した判定にするしきい値</param>
	/// <returns>押下状態</returns>
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

	/// <summary>
	/// フォーマット
	/// </summary>
	std::vector<std::unique_ptr<InputFormatBase>> mFormats;
};

template<InputFormat T>
inline void InputDeviceBase::RegisterFormat()
{
	std::unique_ptr<T> format = std::make_unique<T>();
	format->Init();
	mFormats.emplace_back(std::move(format));
}
