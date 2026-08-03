#pragma once

#include "Utility/Vector.h"

/// <summary>
/// マウスの入力管理
/// </summary>
class Mouse
{
public:

	~Mouse() = default;

	/// <summary>
	/// マウスの座標モード
	/// </summary>
	enum class Mode
	{
		Absolute,	// 絶対座標
		Relative	// 相対座標
	};
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうかを取得する
	/// </summary>
	/// <param name="keyCode">キーコード</param>
	/// <returns>押下状態</returns>
	bool IsDown(int keyCode) const;

public:

	/// <summary>
	/// 絶対座標を取得する
	/// </summary>
	const Vector2& GetPosition() const { return mPosition; }

	/// <summary>
	/// 相対座標を取得する
	/// </summary>
	const Vector2& GetRelative() const { return mRelative; }

	/// <summary>
	/// マウスホイールの回転量を取得する
	/// </summary>
	const Vector2& GetWheelRot() const { return mWheelRot; }

	/// <summary>
	/// 座標モードを設定する
	/// </summary>
	void SetMode(Mode mode);

public:

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static Mouse& GetInstance();

private:

	Mouse();
	// コピーコンストラクタ禁止
	Mouse(const Mouse&) = delete;
	// コピー代入禁止
	Mouse& operator=(const Mouse&) = delete;
	// ムーブ禁止
	Mouse(Mouse&&) = delete;
	// ムーブ代入禁止
	Mouse& operator=(Mouse&&) = delete;

	/// <summary>
	/// 座標情報を更新する
	/// </summary>
	void UpdatePosition();

	/// <summary>
	/// マウスボタンの押下状態
	/// </summary>
	int mState;

	/// <summary>
	/// 絶対座標
	/// </summary>
	Vector2 mPosition;

	/// <summary>
	/// 相対座標
	/// </summary>
	Vector2 mRelative;

	/// <summary>
	/// マウスホイールの回転量
	/// </summary>
	Vector2 mWheelRot;

	/// <summary>
	/// 座標モード
	/// </summary>
	Mode mMode;
};
