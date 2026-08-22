#include "Enemy.h"
#include <cassert>
#include <cmath>
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;

	constexpr Vector3 kCollisionSize{ 50.0f, 50.0f, 50.0f };

	constexpr float kEnduranceTime = 0.5f;
}

Enemy::Enemy(Transform* playerTransform) :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mCollider(nullptr),
	mPlayerTransform(playerTransform)
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
	ResolvePush();

	Vector3 vecToPlayer = mPlayerTransform->localPosition - mTransform->localPosition;
	Vector3 ToPlayerNorm = vecToPlayer.GetNormalize();
	ToPlayerNorm.y = 0.0f;

	float moveDir = mTransform->CalculateWorldRotation().y;
	mMoveVec = Vector3(std::cos(moveDir), 0.0f, std::sin(moveDir));

	mVelocity = ToPlayerNorm * kMoveSpeed;

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
	mTransform->localPosition += mVelocity * TimeManager::GetDeltaTime();

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
	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:

		mCollisionPush += result.normal * result.penetration;

		// •Ç‚Æ‚ÌÕ“Ë
		if (!Math::IsNearZero(result.normal.x))
		{
			mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			mVelocity.z = 0.0f;
		}

		// ’n–Ê‚Æ‚ÌÕ“Ë
		if (result.normal.y > 0.5f)
		{
			mVelocity.y = Math::Max(mVelocity.y, 0.0f);
		}
		break;

	case Tag::Tornado:
	{
		mIsHitTornado = true;

		if (mEnduranceTimer > kEnduranceTime)
		{
			PlayerTornado* tornado = dynamic_cast<PlayerTornado*>(oppCollider->GetOwner());

			tornado->AddPulledNum();

			Destroy(this);
		}
		break;
	}
	}
}

void Enemy::ResolvePush()
{
	if (mCollisionPush != Vector3::Zero)
	{
		mTransform->localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}
