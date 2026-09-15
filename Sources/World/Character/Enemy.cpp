#include "Enemy.h"
#include <memory>
#include <DxLib.h>
#include <imgui.h>
#include "State/StateContext.h"
#include "State/Enemy/StateEnemyFollow.h"
#include "State/Enemy/StateEnemyPatrollingMove.h"
#include "State/Enemy/StateEnemyPatrollingInterpreter.h"
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Param/Param.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 50.0f, 50.0f, 50.0f };

	constexpr float kEnduranceTime = 0.5f;

	const char* const kPatrollingDataPath = "Resources\\MasterData\\TestEnemyMoveData.json";

	const char* const kWaypointDataPath = "Resources\\MasterData\\TestStageWaypoint0.json";

	constexpr float kYawLatency = 0.1f;

	constexpr float kFOV = 80.0f;
	constexpr float kSearchRange = 100.0f;

	constexpr float kDebugForwardLineLen = 50.0f;
}

Enemy::Enemy(Transform* playerTransform, EnemyPatrollingData patrollingData, const std::vector<WaypointGroup>& waypointGroups) :
	mTargetYaw(0.0f),
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mCurrentWaypointID(0),
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
	mStateContext->AddStateToPool(std::make_unique<StateEnemyPatrollingInterpreter>(std::move(patrollingData.waypointActions)));

	//mStateContext->PushState<StateEnemyPatrollingMove>();
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

	float yawDif = mTargetYaw - mTransform->localRotation.y;
	mTransform->localRotation.y += Math::NormalizeRadian(yawDif) * kYawLatency;

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
	Vector3 worldPos = mTransform->CalculateWorldPosition();
	float worldYaw = mTransform->CalculateWorldRotation().y;
	Vector3 forward = Vector3(std::sin(worldYaw), 0.0f, -std::cos(worldYaw));

	// 正面方向に線を引く
	DrawLine3D(worldPos.GetAsDxLibVector(), (worldPos + forward * kDebugForwardLineLen).GetAsDxLibVector(), Color::red.GetAsHexRGB());

	Vector3 fovVec = Vector3(-std::sin(worldYaw + kFOV * 0.5f), 0.0f, std::cos(worldYaw + kFOV * 0.5f));
	DrawLine3D(worldPos.GetAsDxLibVector(), (worldPos + fovVec * kSearchRange).GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
	fovVec = Vector3(-std::sin(worldYaw - kFOV * 0.5f), 0.0f, std::cos(worldYaw - kFOV * 0.5f));
	DrawLine3D(worldPos.GetAsDxLibVector(), (worldPos + fovVec * kSearchRange).GetAsDxLibVector(), Color::yellow.GetAsHexRGB());

	mCollider->GetShape()->DebugDraw(mIsHitTornado ? Color::red : Color::white);

	if (ImGui::Begin("Enemy"))
	{
		float velPtr[] = { mVelocity.x, mVelocity.y, mVelocity.z};
		ImGui::InputFloat3("Velocity", velPtr, "%.1f");

		ImGui::Text("EnduranceTimer : %f", mEnduranceTimer);

		ImGui::Text("IsFoundPlayer : %d", IsFoundPlayer());

		ImGui::End();
	}
}

void Enemy::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:

		//mCollisionPush += result.normal * result.penetration;

		// 壁との衝突
		if (!Math::IsNearZero(result.normal.x))
		{
			//mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			//mVelocity.z = 0.0f;
		}

		// 地面との衝突
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

bool Enemy::IsFoundPlayer() const
{
	// 正面ベクトルを計算
	float worldYaw = mTransform->CalculateWorldRotation().y;
	Vector3 forward = Vector3(-std::sin(worldYaw), 0.0f, std::cos(worldYaw));

	// 敵とプレイヤーの座標を平面上で取得
	Vector3 myPos = mTransform->CalculateWorldPosition();
	myPos.y = 0.0f;
	Vector3 playerPos = GetPlayerTransform()->CalculateWorldPosition();
	playerPos.y = 0.0f;

	// 重なっていたらtrue
	if (myPos == playerPos) return true;

	float distance = (playerPos - myPos).GetLength();
	// 検知範囲外ならfalse
	if (distance >= kSearchRange) return false;

	// 敵からプレイヤーへの法線を計算
	Vector3 toPlayerNorm = (playerPos - myPos) / distance;

	// 視野内かどうか判定
	float dot = forward.Dot(toPlayerNorm);
	return dot < std::cos(kFOV * 0.5f);
}

void Enemy::ResolvePush()
{
	if (mCollisionPush != Vector3::Zero)
	{
		mTransform->localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}
