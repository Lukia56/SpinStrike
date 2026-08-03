#include "InputModifierSwizzleAxis.h"
#include <utility>
#include "Utility/Vector.h"

InputModifierSwizzleAxis::InputModifierSwizzleAxis(Order order) :
	mOrder(order)
{
}

void InputModifierSwizzleAxis::ModifyRaw(Vector3& rawValue)
{
	switch (mOrder)
	{
	case InputModifierSwizzleAxis::Order::XZY:
		std::swap(rawValue.y, rawValue.z);
		break;
	case InputModifierSwizzleAxis::Order::YXZ:
		std::swap(rawValue.x, rawValue.y);
		break;
	case InputModifierSwizzleAxis::Order::YZX:
		std::swap(rawValue.x, rawValue.y);
		std::swap(rawValue.x, rawValue.z);
		break;
	case InputModifierSwizzleAxis::Order::ZYX:
		std::swap(rawValue.x, rawValue.z);
		break;
	case InputModifierSwizzleAxis::Order::ZXY:
		std::swap(rawValue.x, rawValue.y);
		std::swap(rawValue.y, rawValue.z);
		break;
	}
}
