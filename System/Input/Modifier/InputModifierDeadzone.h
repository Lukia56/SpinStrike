#pragma once

#include "IInputModifier.h"

/// <summary>
/// デッドゾーンを設定する
/// </summary>
class InputModifierDeadzone : public IInputModifier
{
public:

	InputModifierDeadzone();
	InputModifierDeadzone(float dzMin, float dzMax);
	~InputModifierDeadzone() = default;

	void ModifyRaw(Vector3& rawValue) override;

private:

	// デッドゾーンの範囲
	float mDeadzoneMin, mDeadzoneMax;
};
