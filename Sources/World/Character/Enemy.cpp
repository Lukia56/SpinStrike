#include "Enemy.h"
#include <cassert>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "System/TimeManager.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 50.0f, 50.0f, 50.0f };

	constexpr float kEnduranceTime = 0.5f;
}

Enemy::Enemy() :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mCollider(nullptr)
{
	SetTag(Tag::Enemy);

	mCollider = std::make_unique<Collider3D>(
				std::make_unique<Collision::AABB3D>(kCollisionSize),
				this,
				Collision::Tag::Body);
}

void Enemy::Init()
{
}

void Enemy::Finalize()
{
}

void Enemy::Update()
{
	if (mIsHitTornado)
	{
		mEnduranceTimer += TimeManager::GetDeltaTime();
	}
	else
	{
		mEnduranceTimer = 0.0f;
	}
}

void Enemy::PhysicsUpdate()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);

	mIsHitTornado = false;
}

void Enemy::Draw()
{
}

void Enemy::DebugDraw()
{
	mCollider->GetShape()->DebugDraw(mIsHitTornado ? Color::red : Color::white);

	if (ImGui::Begin("Enemy"))
	{
		ImGui::Text("EnduranceTimer : %f", mEnduranceTimer);

		ImGui::End();
	}
}

void Enemy::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (oppCollider->GetOwner()->GetTag() != Tag::Tornado) return;

	mIsHitTornado = true;

	if (mEnduranceTimer > kEnduranceTime)
	{
		PlayerTornado* tornado = dynamic_cast<PlayerTornado*>(oppCollider->GetOwner());

		tornado->AddPulledNum();

		Destroy(this);
	}
}
