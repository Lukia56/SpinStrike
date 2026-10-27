#include "PlayerTornado.h"
#include <cmath>
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "System/InputManager.h"
#include "System/PlayerDataManager.h"
#include "System/TimeManager.h"

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

	const PlayerParam& param = PlayerDataManager::GetInstance().GetPlayerParam();
	
	Vector3 collisionOffset = Vector3(0.0f, param.spinTornadoRadius, 0.0f);

	mAttackCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(param.spinTornadoRadius, collisionOffset),
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
	mAttackCollider->Update();
}

void PlayerTornado::Draw()
{
}

void PlayerTornado::DebugDraw()
{
	mAttackCollider->DebugDraw();

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

	mSpinPreStartTimer = PlayerDataManager::GetInstance().GetPlayerParam().spinPreStartTime;
	mSpinStamina = PlayerDataManager::GetInstance().GetPlayerParam().spinStaminaDuration;
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

	mSpinCooldownTimer = PlayerDataManager::GetInstance().GetPlayerParam().spinCooldownTime;

	mAttackCollider->Disable();

	CreateBullet();
}

void PlayerTornado::CreateBullet()
{
	if (mPulledNum <= 0) return;

	float yaw = mTransform->GetParent()->CalculateWorldRotation().y;
	Vector3 moveVec = Vector3(-std::sin(yaw), 0.0f, -std::cos(yaw));

	mBulletManager->CreateBullet(mTransform->CalculateWorldPosition(), moveVec);

	mPulledNum = 0;
}
