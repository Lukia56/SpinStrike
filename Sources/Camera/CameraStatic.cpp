#include "CameraStatic.h"
#include "Utility/Vector.h"

namespace
{
	constexpr Vector3 kEyePosition = Vector3(0.0f, 100.0f, -256.0f);
	constexpr Vector3 kTargetPosition = Vector3(0.0f, 100.0f, 0.0f);
}

void CameraStatic::Update(Camera::View& view)
{
	view.eyePosition = kEyePosition;
	view.targetPosition = kTargetPosition;
}
