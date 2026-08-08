#pragma once

/// <summary>
/// キーボードの入力管理
/// </summary>
class Keyboard
{
public:

	~Keyboard() = default;

	void Update();

	bool IsDown(int keyCode) const;

	static Keyboard& GetInstance();

private:

	Keyboard() = default;

	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	Keyboard(Keyboard&&) = delete;
	Keyboard& operator=(Keyboard&&) = delete;

	char mState[256];
};
