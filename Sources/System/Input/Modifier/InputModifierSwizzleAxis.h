#pragma once

#include "IInputModifier.h"

/// <summary>
/// ’l‚ğ“ü‚ê‘Ö‚¦‚é
/// </summary>
class InputModifierSwizzleAxis : public IInputModifier
{
public:

	/// <summary>
	/// ²‚ğ“ü‚ê‘Ö‚¦‚é‡”Ô
	/// </summary>
	enum class Order
	{
		XZY,
		YXZ,
		YZX,
		ZYX,
		ZXY
	};

	InputModifierSwizzleAxis(Order order);
	~InputModifierSwizzleAxis() = default;

	void ModifyRaw(Vector3& rawValue) override;

private:

	/// <summary>
	/// ²‚ğ“ü‚ê‘Ö‚¦‚é‡”Ô
	/// </summary>
	Order mOrder;
};
