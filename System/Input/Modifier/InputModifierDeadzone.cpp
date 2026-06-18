#include "InputModifierDeadzone.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	constexpr float kDefaultDeadzoneMin = 0.125f;
	constexpr float kDefaultDeadzoneMax = 0.925f;
}

InputModifierDeadzone::InputModifierDeadzone() :
	mDeadzoneMin(kDefaultDeadzoneMin),
	mDeadzoneMax(kDefaultDeadzoneMax)
{
}

InputModifierDeadzone::InputModifierDeadzone(float dzMin, float dzMax) :
	mDeadzoneMin(dzMin),
	mDeadzoneMax(dzMax)
{
}

void InputModifierDeadzone::ModifyRaw(Vector3& rawValue)
{
	Vector2 filtered = Math::Filter2D(rawValue.x, rawValue.y, 1.0f, mDeadzoneMin, mDeadzoneMax);
	rawValue = Vector3(filtered.x, filtered.y, 0.0f);
}
