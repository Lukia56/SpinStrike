#pragma once

#include "InputFormatBase.h"

/// <summary>
/// ƒ}ƒEƒX‚ÌˆÚ“®“ü—Í‚ðŽæ“¾‚·‚é
/// </summary>
class InputFormatMouseDelta : public InputFormatBase
{
public:

	InputFormatMouseDelta() = default;
	~InputFormatMouseDelta() = default;

	void Init() override;

	bool CheckButtonState(const KeyCode::Button keyCode) const override;

	Vector3 GetValue(const KeyCode::Button keyCode) const override;
};
