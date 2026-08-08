#pragma once

#include "IInputModifier.h"

/// <summary>
/// ’l‚ğ”½“]‚³‚¹‚é
/// </summary>
class InputModifierNegate : public IInputModifier
{
public:

	InputModifierNegate(bool x, bool y, bool z);
	~InputModifierNegate() = default;

	void ModifyRaw(Vector3& rawValue) const override;

private:

	// ’l‚ğ”½“]‚³‚¹‚é¬•ª
	bool mX, mY, mZ;
};
