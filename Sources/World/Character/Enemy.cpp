#include "Enemy.h"
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "State/StateContext.h"
#include "State/Enemy/StateEnemyFollow.h"
//#include "State/Enemy/StateEnemyPatrolling.h"
#include "State/Enemy/StateEnemyPatrollingMove.h"
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Param/Param.h"
#include "System/TimeManager.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 50.0f, 50.0f, 50.0f };

	constexpr float kEnduranceTime = 0.5f;

	const char* const kPatrollingDataPath = "Resources\\MasterData\\TestEnemyMoveData.json";

	const char* const kWaypointDataPath = "Resources\\MasterData\\TestStageWaypoint0.json";
}

Enemy::Enemy(Transform* playerTransform, EnemyPatrollingData patrollingData, const std::vector<WaypointGroup>& waypointGroups) :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mCollider(nullptr),
	mStateContext(nullptr),
	mPlayerTransform(playerTransform)
{
	SetTag(Tag::Enemy);

	mCollider = std::make_unique<Collider3D>(
				std::make_unique<Collision::AABB3D>(kCollisionSize),
				this,
				Collision::Tag::Body);

	WaypointGroup waypointGroup{};
	if (patrollingData.moveData.waypointGroupID < waypointGroups.size())
	{
		waypointGroup = waypointGroups[patrollingData.moveData.waypointGroupID];
	}
	
	mStateContext = std::make_unique<StateContext<Enemy>>(this);
	mStateContext->AddStateToPool(std::make_unique<StateEnemyFollow>());
	mStateContext->AddStateToPool(std::make_unique<StateEnemyPatrollingMove>(patrollingData.moveData, waypointGroup));

	mStateContext->PushState<StateEnemyPatrollingMove>();
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

	mStateContext->Update();

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
		float velPtr[] = { mVelocity.x, mVelocity.y, mVelocity.z};
		ImGui::InputFloat3("Velocity", velPtr, "%.1f");

		ImGui::Text("EnduranceTimer : %f", mEnduranceTimer);

		ImGui::End();
	}
}

void Enemy::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:

		//mCollisionPush += result.normal * result.penetration;

		// •Ç‚Æ‚ÌÕ“Ë
		if (!Math::IsNearZero(result.normal.x))
		{
			//mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			//mVelocity.z = 0.0f;
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
