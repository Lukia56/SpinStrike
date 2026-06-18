#pragma once

#include <array>
#include <unordered_map>
#include "Input/Literal/InputActions.h"
#include "Input/Literal/InputProperty.h"
#include "Utility/Vector.h"

class InputDeviceBase;
class IInputModifier;

// 入力デバイスであることを表すコンセプト
template <class T>
concept InputDevice = std::derived_from<T, InputDeviceBase>;

/// <summary>
/// 入力処理の管理をするクラス
/// </summary>
class InputManager
{
public:

	~InputManager() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// 押されたかどうか
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <returns>押下状態</returns>
	bool IsDown(Input::Action action) const;

	/// <summary>
	/// 押された瞬間かどうか
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <returns>押下状態</returns>
	bool IsPressed(Input::Action action) const;

	/// <summary>
	/// 離された瞬間かどうか
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <returns>押下状態</returns>
	bool IsReleased(Input::Action action) const;

	/// <summary>
	/// 一定時間押されているか
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <param name="frame">押した判定にするしきい値</param>
	/// <returns>押下状態</returns>
	bool IsHeld(Input::Action action, int frame) const;

	/// <summary>
	/// floatのアナログ値として取得する
	/// </summary>
	float GetAsFloat(Input::Action action) const;
	
	/// <summary>
	/// Vector2のアナログ値として取得する
	/// </summary>
	Vector2 GetAsVector2(Input::Action action) const;

	/// <summary>
	/// Vector3のアナログ値として取得する
	/// </summary>
	Vector3 GetAsVector3(Input::Action action) const;

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static InputManager& GetInstance();

public:

	void SetActiveActionMap(Input::ActionMap map, bool flag) { mActionMapState[static_cast<size_t>(map)] = flag; }

private:

	InputManager() = default;
	// コピーコンストラクタ禁止
	InputManager(const InputManager&) = delete;
	// コピー代入禁止
	InputManager& operator=(const InputManager&) = delete;
	// ムーブ禁止
	InputManager(InputManager&&) = delete;
	// ムーブ代入禁止
	InputManager& operator=(InputManager&&) = delete;

	// 入力方法
	enum class InputType
	{
		Down,
		Pressed,
		Released,
		Held
	};

	/// <summary>
	/// アクションのボタンが入力方法の条件を満たしているかチェック
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <param name="inputType">入力方法</param>
	/// <param name="frame">押した判定にするしきい値</param>
	bool GetState(Input::Action action, InputType inputType, int frame = 0) const;

	/// <summary>
	/// アナログ値を取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetValue(Input::Action action) const;

	/// <summary>
	/// アクションデータにボタンを割り当てる
	/// </summary>
	/// <param name="action">アクションID</param>
	/// <param name="device">入力デバイス</param>
	/// <param name="button">キーコード</param>
	/// <param name="modifiers">値を加工する機能の配列</param>
	/// <param name="slot">ゲームパッドの識別番号</param>
	void Bind(Input::Action action, Input::Device device, KeyCode::Button button, std::vector<std::shared_ptr<IInputModifier>> modifiers = {}, Input::PadSlot slot = Input::PadSlot::Player1);

	/// <summary>
	/// 入力デバイスを登録する
	/// </summary>
	/// <typeparam name="T">登録したいデバイス</typeparam>
	/// <param name="type">デバイスの種類</param>
	template <InputDevice T>
	void RegisterDevice(Input::Device type);

private:

	/// <summary>
	/// アクションのデータ
	/// </summary>
	std::array<Input::ActionProperty, static_cast<size_t>(Input::Action::Length)> mActions;

	/// <summary>
	/// 入力デバイス
	/// </summary>
	std::unordered_map<Input::Device, std::unique_ptr<InputDeviceBase>> mDevices;

	/// <summary>
	/// アクションマップの有効状態
	/// </summary>
	std::array<bool, static_cast<size_t>(Input::ActionMap::Length)> mActionMapState;
};

template<InputDevice T>
inline void InputManager::RegisterDevice(Input::Device type)
{
	std::unique_ptr<T> device = std::make_unique<T>();
	device->Init();
	mDevices.emplace(type, std::move(device));
}
