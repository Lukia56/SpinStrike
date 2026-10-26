#include "PlayerTornado.h"
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kCollisionRadius = 150.0f;

	constexpr Vector3 kCollisionOffsetPos{ 0.0f, kCollisionRadius / 2.0f, 0.0f };

	constexpr float kSpinCooldownTime = 0.75f;
	constexpr float kSpinPreStartTime = 0.1f;
	constexpr float kSpinStaminaDuration = 3.5f;
}

PlayerTornado::PlayerTornado(PlayerBulletManager* bulletManager) :
	mIsSpinning(false),
	mSpinStamina(0.0f),
	mSpinPreStartTimer(0.0f),
	mSpinCooldownTimer(0.0f),
	mPulledNum(0),
	mAttackCollider(nullptr),
	mBulletManager(bulletManager)
{
}

void PlayerTornado::Init()
{
	SetTag(Tag::Tornado);

	mAttackCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(kCollisionRadius, kCollisionOffsetPos),
		this,
		Collision::Tag::Body,
		false
	);
}

void PlayerTornado::Update()
{
	SpinAction(TimeManager::GetDeltaTime());
}

void PlayerTornado::PhysicsUpdate()
{
	mAttackCollider->GetShape()->SetPosition(mTransform->CalculateWorldPosition());
}

void PlayerTornado::Draw()
{
}

void PlayerTornado::DebugDraw()
{
	if (mAttackCollider->IsEnabled()) mAttackCollider->GetShape()->DebugDraw();

	if (ImGui::Begin("Tornado"))
	{
		ImGui::Text("IsSpinning: %d", mIsSpinning);
		ImGui::Text("SpinStamina: %f", mSpinStamina);
		ImGui::Text("SpinCooldownTimer: %f", mSpinCooldownTimer);
		ImGui::Text("SpinPreStartTimer: %f", mSpinPreStartTimer);

		ImGui::Text("PulledCount = %d", mPulledNum);

		ImGui::End();
	}
}

void PlayerTornado::CreateBullet(const Vector3& moveVec)
{
	if (mPulledNum <= 0) return;

	mBulletManager->CreateBullet(mTransform->CalculateWorldPosition(), moveVec);

	mPulledNum = 0;
}

void PlayerTornado::SpinAction(float deltaTime)
{
	// クールダウン中は処理を行わない
	if (mSpinCooldownTimer > 0.0f)
	{
		mSpinCooldownTimer -= deltaTime;
		return;
	}

	ActivateSpin(deltaTime);

	// スピン中
	if (mAttackCollider->IsEnabled())
	{
		// スタミナを消費する
		if (mSpinStamina > 0.0f)
		{
			mSpinStamina -= deltaTime;
		}

		DeactivateSpin();
	}
}

void PlayerTornado::ActivateSpin(float deltaTime)
{
	StartSpin();

	if (!mIsSpinning) return;
	if (mAttackCollider->IsEnabled()) return;

	if (mSpinPreStartTimer > 0.0f)
	{
		mSpinPreStartTimer -= deltaTime;
	}
	else
	{
		mAttackCollider->Enable();
	}
}

void PlayerTornado::StartSpin()
{
	if (!InputManager::GetInstance().IsPressed(Input::Action::Spin)) return;
	
	mIsSpinning = true;

	mSpinPreStartTimer = kSpinPreStartTime;
	mSpinStamina = kSpinStaminaDuration;
}

void PlayerTornado::DeactivateSpin()
{
	if (mSpinStamina < 0.0f
	|| !InputManager::GetInstance().IsDown(Input::Action::Spin))
	{
		EndSpin();
	}
}

void PlayerTornado::EndSpin()
{
	mIsSpinning = false;

	mSpinCooldownTimer = kSpinCooldownTime;

	mAttackCollider->Disable();
}
