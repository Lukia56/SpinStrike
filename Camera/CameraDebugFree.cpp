#include "CameraDebugFree.h"
#include <cmath>
#include <imgui.h>
#include "System/InputManager.h"
#include "System/Input/Mouse.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	constexpr float kMoveSpeed = 600.0f;
	constexpr float kRotSpeed = Math::ToRadian(10.0f);

	constexpr float kDistanceToTarget = 100.0f;

	constexpr float kPitchLimit = Math::ToRadian(89.0f);

	constexpr float kCrossHairLength = 25.0f;
}

void CameraDebugFree::Update(Camera::View& view)
{
	Look();

	Move();

	float pitchRad = mRotation.x;
	float yawRad = mRotation.y;

	Vector3 forward;
	forward.x = std::cos(pitchRad) * std::sin(yawRad);
	forward.y = std::sin(pitchRad);
	forward.z = std::cos(pitchRad) * std::cos(yawRad);

	view.eyePosition = mPosition;
	view.targetPosition = mPosition + forward * kDistanceToTarget;
}

void CameraDebugFree::DebugDraw()
{
	if (ImGui::Begin("Camera"))
	{
		float posPtr[] = { mPosition.x, mPosition.y, mPosition.z };
		ImGui::InputFloat3("Position", posPtr, "%.1f");

		float rotPtr[] = { Math::ToDegree(mRotation.x), Math::ToDegree(mRotation.y), Math::ToDegree(mRotation.z) };
		ImGui::InputFloat3("Rotation", rotPtr, "%.1f");

		ImGui::End();
	}

	DrawCrossHair();
}

void CameraDebugFree::Look()
{
	Vector2 relative = Mouse::GetInstance().GetRelative();
	if (relative != Vector2::Zero && Mouse::GetInstance().IsDown(MOUSE_INPUT_RIGHT))
	{
		mRotation += Vector3(-relative.y, relative.x, 0.0f) * Math::ToRadian(1.0f);
	}

	if (relative == Vector2::Zero)
	{
		mRotation += InputManager::GetInstance().GetAsVector3(Input::Action::Look) * kRotSpeed;
	}

	mRotation.x = Math::Clamp(mRotation.x, -kPitchLimit, kPitchLimit);
	mRotation.y = Math::NormalizeRadian(mRotation.y);
}

void CameraDebugFree::Move()
{
	float pitchRad = mRotation.x;
	float yawRad = mRotation.y;

	Vector3 forward;
	forward.x = std::cos(pitchRad) * std::sin(yawRad);
	forward.y = std::sin(pitchRad);
	forward.z = std::cos(pitchRad) * std::cos(yawRad);

	Vector3 right;
	right.x = std::cos(yawRad);
	right.y = 0.0f;
	right.z = -std::sin(yawRad);

	Vector3 moveDir = InputManager::GetInstance().GetAsVector3(Input::Action::Move);
	mPosition += forward * kMoveSpeed * moveDir.z * TimeManager::GetDeltaTime();
	mPosition += right * kMoveSpeed * moveDir.x * TimeManager::GetDeltaTime();

	mPosition.y += kMoveSpeed * InputManager::GetInstance().GetAsFloat(Input::Action::Fly) * TimeManager::GetDeltaTime();
}

void CameraDebugFree::DrawCrossHair()
{
	// âÊñ ÇÃíÜêSç¿ïWÇéÊìæ
	int cx, cy;
	GetWindowSize(&cx, &cy);
	cx *= 0.5f;
	cy *= 0.5f;

	float pitchRad = mRotation.x;
	float yawRad = mRotation.y;

	// Xé≤
	DrawLine(
		cx, cy,
		cx + std::cos(yawRad) * kCrossHairLength,
		cy + -std::sin(yawRad) * -std::sin(pitchRad) * kCrossHairLength,
		Color::red.GetAsHexRGB(), 2);
	// Zé≤
	DrawLine(
		cx, cy,
		cx + -std::sin(yawRad) * kCrossHairLength,
		cy + -std::cos(yawRad) * -std::sin(pitchRad) * kCrossHairLength,
		Color::blue.GetAsHexRGB(), 2);
	// Yé≤
	DrawLine(
		cx, cy,
		cx,
		cy + -std::cos(pitchRad) * kCrossHairLength,
		Color::green.GetAsHexRGB(), 2);
}
