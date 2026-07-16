#pragma once

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
};
