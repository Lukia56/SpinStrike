#include "Mouse.h"
#include <DxLib.h>
#include "Utility/Vector.h"

void Mouse::Update()
{
	mState = GetMouseInput();
	mWheelRot.x = GetMouseHWheelRotVolF();
	mWheelRot.y = GetMouseWheelRotVolF();

	UpdatePosition();

	// 相対座標モードならマウスカーソルを固定する
	if (mMode == Mode::Relative)
	{
		int width, height;
		GetWindowSize(&width, &height);

		Vector2 halfSize = Vector2(width * 0.5f, height * 0.5f);

		SetMousePoint(static_cast<int>(halfSize.x), static_cast<int>(halfSize.y));
		mPosition = halfSize;
	}
}

bool Mouse::IsDown(int keyCode) const
{
	return mState & keyCode;
}

void Mouse::SetMode(Mode mode)
{
	mMode = mode;

	if (mode == Mode::Relative) SetMouseDispFlag(false);
	else SetMouseDispFlag(true);
}

Mouse& Mouse::GetInstance()
{
	static Mouse instance;

	return instance;
}

Mouse::Mouse() :
	mState(0),
	mPosition(Vector2::Zero),
	mRelative(Vector2::Zero),
	mWheelRot(Vector2::Zero),
	mMode(Mode::Absolute)
{
}

void Mouse::UpdatePosition()
{
	// マウスの座標を取得
	int x, y;
	GetMousePoint(&x, &y);
	Vector2 pos = Vector2(static_cast<float>(x), static_cast<float>(y));

	// 相対座標を更新
	mRelative = pos - mPosition;

	// 絶対座標を更新
	mPosition = pos;
}
