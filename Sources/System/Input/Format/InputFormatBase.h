#pragma once

#include <unordered_map>
#include "../Literal/KeyCodes.h"
#include "Utility/Vector.h"

/// <summary>
/// キーコードから入力状態を検知する基底
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

	virtual bool CheckButtonState(const KeyCode::Button keyCode) const = 0;

	/// <summary>
	/// アナログ値を取得する
	/// </summary>
	virtual Vector3 GetValue(const KeyCode::Button keyCode) const = 0;

	/// <summary>
	/// 自作キーコードを登録する
	/// </summary>
	/// <param name="myKeyCode">自作キーコード</param>
	/// <param name="keyCode">元のキーコード</param>
	void RegisterKeyCode(const KeyCode::Button myKeyCode, const unsigned int keyCode);

public:

	const LinkToKeyCode& GetLinkToKeyCode() const { return mLinkToKeyCode; };

private:

	/// <summary>
	/// 自作キーコードを元のキーコードに紐づけるマップ
	/// </summary>
	LinkToKeyCode mLinkToKeyCode;
};
