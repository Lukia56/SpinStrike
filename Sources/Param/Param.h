#pragma once

#include <string>
#include "TempParam.h"
#include "Collision/CollisionTag.h"
#include "Utility/Vector.h"
#include "World/Component/Transform.h"

struct PlayerParam
{
	float walkSpeed;
	float walkAccel;

	float dashSpeed;
	float dashAccel;

	float jumpForce;
	float jumpCancelThreshold;
	float jumpBufferTime;

	float wallJumpVerticalForce;
	float wallJumpHorizontalForce;
	float wallJumpIgnoreMoveInputTime;

	float stickWallFallSpeed;
	float stickWallCancelTimeThreshold;
	float stickWallCancelMoveVectorThreshold;

	float airResistanceCoef;
	float gravity;
};

struct AABBColliderParam
{
	Vector3 size;
	Vector3 offsetPos;
	Collision::Tag collisionTag;
};

struct AnimationParam
{
	int animIndex;
	bool isLoop;
	bool isForcePlay;
};

struct StageObjectParam
{
	std::string name;
	TempTransform transform;
	TempBounds bounds;
};
