#pragma once

#include <cassert>
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace Camera
{
	struct View
	{
		Vector3 eyePosition = Vector3::Zero;

		Vector3 targetPosition = Vector3::One;

		// デグリー角
		float fov = 0.0f;

		float nearClip;

		float farClip;

		Vector3 GetRawForward() const
		{
			return targetPosition - eyePosition;
		}

		Vector3 CalculateForward() const
		{
			Vector3 forward = GetRawForward();

			if (Math::NearyEqual(forward.GetSqLength(), 0.0f))
			{
				assert(false && "Camera::View // 0除算が行われようとしました");
				return Vector3::Zero;
			}
			
			return forward.GetNormalize();
		}

		Vector3 CalculatePlaneVecForward() const
		{
			Vector3 forward = GetRawForward();
			forward.y = 0.0f;

			if (Math::NearyEqual(forward.GetSqLength(), 0.0f))
			{
				assert(false && "Camera::View // 0除算が行われようとしました");
				return Vector3::Zero;
			}

			return forward.GetNormalize();
		}

		Vector3 CalculatePlaneVecRight() const
		{
			Vector3 forward = CalculatePlaneVecForward();

			return Vector3(forward.z, 0.0f, -forward.x);
		}
	};

	enum class Type
	{
		Static,
		DebugFree,
		Follow,
		Max,
	};
}
