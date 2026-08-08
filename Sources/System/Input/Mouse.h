#pragma once

#include "Utility/Vector.h"

/// <summary>
/// マウスの入力管理をする
/// </summary>
class Mouse
{
public:

	/// <summary>
	/// マウスの座標モード
	/// </summary>
	enum class Mode
	{
		Absolute,
		Relative
	};

	~Mouse() = default;
	
	void Update();

	bool IsDown(int keyCode) const;

public:

	const Vector2& GetAbsolutePos() const { return mAbsolutePos; }

	const Vector2& GetRelativePos() const { return mRelativePos; }

	const Vector2& GetWheelRot() const { return mWheelRot; }

	void SetMode(Mode mode);

public:

	static Mouse& GetInstance();

private:

	Mouse();

	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(Mouse&&) = delete;

	void UpdatePosition();

	int mState;

	Vector2 mAbsolutePos;

	Vector2 mRelativePos;

	Vector2 mWheelRot;

	Mode mMode;
};
