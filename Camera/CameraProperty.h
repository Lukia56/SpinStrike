#pragma once

#include "Utility/Vector.h"

namespace Camera
{
	struct View
	{
		Vector3 eyePosition = Vector3::Zero;

		Vector3 targetPosition = Vector3::One;

		// ÉfÉOÉäÅ[äp
		float fov = 0.0f;

		float nearClip;

		float farClip;
	};

	enum class Type
	{
		Static,
		DebugFree,
		Max,
	};
}
