#pragma once

#include "Utility/Vector.h"

/// <summary>
/// 値を加工するクラスのインターフェイス
/// </summary>
class IInputModifier
{
public:

	IInputModifier() = default;
	virtual ~IInputModifier() = default;

	virtual void ModifyRaw(Vector3& rawValue) = 0;
};
