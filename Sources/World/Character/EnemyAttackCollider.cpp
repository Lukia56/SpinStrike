#include "EnemyAttackCollider.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "System/TimeManager.h"

EnemyAttackCollider::EnemyAttackCollider(float attackRadius) :
	mActiveTimer(0.0f),
	mCollider(nullptr)
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(attackRadius),
		this,
		Collision::Tag::Attack,
		false,
		false
	);
}

void EnemyAttackCollider::Init()
{
	SetTag(Tag::Enemy);
}

void EnemyAttackCollider::Update()
{
	if (!mCollider->IsEnabled()) return;

	if (mActiveTimer > 0.0f)
	{
		mActiveTimer -= TimeManager::GetDeltaTime();
	}
	else
	{
		mCollider->Disable();
	}
}

void EnemyAttackCollider::PhysicsUpdate()
{
	mCollider->Update();
}

void EnemyAttackCollider::DebugDraw()
{
	mCollider->DebugDraw(Color::red);
}

void EnemyAttackCollider::Setup(float duration)
{
	mCollider->Enable();

	mActiveTimer = duration;
}
