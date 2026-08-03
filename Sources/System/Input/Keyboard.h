#pragma once

/// <summary>
/// キーボードの入力管理
/// </summary>
class Keyboard
{
public:

	~Keyboard() = default;

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

	/// <summary>
	/// インスタンスの生成、取得を行う
	/// </summary>
	static Keyboard& GetInstance();

private:

	Keyboard() = default;
	// コピーコンストラクタ禁止
	Keyboard(const Keyboard&) = delete;
	// コピー代入禁止
	Keyboard& operator=(const Keyboard&) = delete;
	// ムーブ禁止
	Keyboard(Keyboard&&) = delete;
	// ムーブ代入禁止
	Keyboard& operator=(Keyboard&&) = delete;

	/// <summary>
	/// キーボードの押下状態
	/// </summary>
	char mState[256];
};
