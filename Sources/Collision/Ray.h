#pragma once

#include <cfloat>
#include "Utility/Vector.h"

namespace Collision
{
	struct Ray
	{
		Vector3 position{};

		Vector3 direction{};

		float maxDistance = FLT_MAX;
	};

	struct RaycastResult
	{
		bool isHit = false;

		Vector3 collidePos{};

		float distance = 0.0f;
	};
}
