#include "InputModifierNegate.h"
#include "Utility/Vector.h"

InputModifierNegate::InputModifierNegate(bool x, bool y, bool z) :
	IInputModifier(),
	mX(x),
	mY(y),
	mZ(z)
{
}

void InputModifierNegate::ModifyRaw(Vector3& rawValue)
{
	if (mX) rawValue.x *= -1;
	if (mY) rawValue.y *= -1;
	if (mZ) rawValue.z *= -1;
}
