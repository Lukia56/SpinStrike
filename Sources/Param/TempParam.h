#pragma once

#include "Utility/Vector.h"

struct TempTransform
{
	Vector3 position{};
	Vector3 rotation{};
	Vector3 scale{};
};

struct TempBounds
{
	Vector3 size{};
	Vector3 offsetPos{};
};
