#pragma once

#include <string>
#include "TempParam.h"
#include "Collision/CollisionTag.h"
#include "Utility/Vector.h"
#include "World/Component/Transform.h"

struct WindowConfigs
{
	std::string windowText = "";
	int width = 0;
	int height = 0;
	int colorBit = 0;
};

struct PlayerParam
{
	float walkSpeed = 0.0f;
	float walkAccel = 0.0f;

	float dashSpeed = 0.0f;
	float dashAccel = 0.0f;

	float jumpForce = 0.0f;
	float jumpCancelThreshold = 0.0f;
	float jumpBufferTime = 0.0f;

	float wallJumpVerticalForce = 0.0f;
	float wallJumpHorizontalForce = 0.0f;
	float wallJumpIgnoreMoveInputTime = 0.0f;

	float stickWallFallSpeed = 0.0f;
	float stickWallCancelTimeThreshold = 0.0f;
	float stickWallCancelMoveVectorThreshold = 0.0f;

	float spinMoveSpeed = 0.0f;
	float spinMoveAccel = 0.0f;
	float spinCooldownTime = 0.0f;
	float spinPreStartTime = 0.0f;
	float spinStaminaDuration = 0.0f;

	float airResistanceCoef = 0.0f;
	float gravity = 0.0f;
};

struct AABBColliderParam
{
	Vector3 size{};
	Vector3 offsetPos{};
	Collision::Tag collisionTag = Collision::Tag::Invalid;
};

struct AnimationParam
{
	int animIndex = 0;
	bool isLoop = false;
	bool isForcePlay = false;
};

struct StageObjectParam
{
	std::string name = "";
	TempTransform transform{};
	TempBounds bounds{};
};

struct StageModelData
{
	std::string objectName = "";
	std::string filePath = "";
};
