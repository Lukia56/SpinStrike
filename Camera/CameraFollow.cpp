#include "CameraFollow.h"
#include "World/Components/Transform.h"

namespace
{
	constexpr float kDistance = 100.0f;
}

CameraFollow::CameraFollow(Transform* target) :
	mTarget(target)
{
}

void CameraFollow::Update(Camera::View& view)
{
	Vector3 targetPos = mTarget->CalculateWorldPosition();

	mPosition = targetPos;
	mPosition.z += kDistance;

	view.eyePosition = mPosition;
	view.targetPosition = targetPos;
}
