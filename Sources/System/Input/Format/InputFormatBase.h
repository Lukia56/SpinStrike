#pragma once

#include <unordered_map>
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

/// <summary>
/// キーコードから入力状態を検知するクラス
/// </summary>
class InputFormatBase
{
public:

	using LinkToKeyCode = std::unordered_map<KeyCode::Button, unsigned int>;

	InputFormatBase() = default;
	virtual ~InputFormatBase() = default;

	/// <summary>
	/// ここで自作キーコードを登録する
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <param name="myKeyCode">自作キーコード</param>
	/// <returns>押されていたらtrue</returns>
	virtual bool CheckButtonState(const KeyCode::Button keyCode) = 0;

	/// <summary>
	/// アナログ値を取得する
	/// </summary>
	virtual Vector3 GetValue(const KeyCode::Button keyCode) = 0;

	/// <summary>
	/// 自作キーコードを登録する
	/// </summary>
	/// <param name="myKeyCode">自作キーコード</param>
	/// <param name="keyCode">元のキーコード</param>
	void RegisterKeyCode(const KeyCode::Button myKeyCode, const unsigned int keyCode);

public:

	/// <summary>
	/// キーコードの紐づけを取得する
	/// </summary>
	/// <returns>自作キーコードを元のキーコードに紐づけるマップ</returns>
	const LinkToKeyCode& GetLinkToKeyCode() const { return mLinkToKeyCode; };

private:

	/// <summary>
	/// 自作キーコードを元のキーコードに紐づけるマップ
	/// </summary>
	LinkToKeyCode mLinkToKeyCode;
};
