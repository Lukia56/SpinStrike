#pragma once

#include <string>
#include "TempParam.h"
#include "Utility/Vector.h"
#include "World/Components/CollisionTag.h"
#include "World/Components/Transform.h"

struct PlayerParam
{
	float walkSpeed;
	float walkAccel;

	float dashCoef;

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
