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

	constexpr float kFovHAngle = 80.0f;
	constexpr float kFovVDistance = 80.0f;
	constexpr float kSearchRange = 200.0f;

	constexpr float kDebugForwardLineLen = 50.0f;

	constexpr int kDebugFOVQuolity = 16;
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
}

void Enemy::Init()
{
	SetTag(Tag::Enemy);

	mStateContext->PushState<StateEnemyPatrollingMove>();
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

	// 視野範囲を描画
	DebugDrawFOV();

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

		mCollisionPush += result.normal * result.penetration;

		// 壁との衝突
		if (!Math::IsNearZero(result.normal.x))
		{
			mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			mVelocity.z = 0.0f;
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
	// ゲームシステム上垂直方向を内積で計算する必要はないため、
	// 視野の範囲は扇形の柱状として処理する

	Vector3 myPos = mTransform->CalculateWorldPosition();
	Vector3 playerPos = GetPlayerTransform()->CalculateWorldPosition();

	if (std::abs(playerPos.y - myPos.y) > kFovVDistance) return false;

	// 検知範囲を水平方向だけ調べるために、敵とプレイヤーの座標を平面上にいるものとする
	myPos.y = 0.0f;
	playerPos.y = 0.0f;

	// 重なっていると0割りが発生するためチェック
	if (myPos == playerPos) return true;

	// 検知範囲外かチェック
	float distance = (playerPos - myPos).GetLength();
	if (distance > kSearchRange) return false;

	Vector3 toPlayerNorm = (playerPos - myPos) / distance;

	float worldYaw = mTransform->CalculateWorldRotation().y;
	Vector3 forward = Vector3(-std::sin(worldYaw), 0.0f, std::cos(worldYaw));

	// 視野内かどうか判定
	float dot = forward.Dot(toPlayerNorm);
	return dot < std::cos(Math::ToRadian(kFovHAngle * 0.5f) + Math::kPiOver2);
}

void Enemy::ResolvePush()
{
	if (mCollisionPush != Vector3::Zero)
	{
		mTransform->localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}

void Enemy::DebugDrawFOV()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();
	float worldYaw = -mTransform->CalculateWorldRotation().y;

	constexpr float fovRad = Math::ToRadian(kFovHAngle);

	float startRot = worldYaw - fovRad * 0.5f + Math::kPiOver2;

	Vector3 originPoint = worldPos;
	// 上下と中心に扇形を描画
	for (int i = 0; i < 3; i++)
	{
		originPoint.y = worldPos.y + kFovVDistance * (i - 1);

		// 半径を描画
		Vector3 fovLeftEdgePoint = originPoint + Vector3(std::cos(startRot), 0.0f, -std::sin(startRot)) * kSearchRange;
		DrawLine3D(originPoint.GetAsDxLibVector(), fovLeftEdgePoint.GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
		Vector3 fovRightEdgePoint = originPoint + Vector3(std::cos(startRot + fovRad), 0.0f, -std::sin(startRot + fovRad)) * kSearchRange;
		DrawLine3D(originPoint.GetAsDxLibVector(), fovRightEdgePoint.GetAsDxLibVector(), Color::yellow.GetAsHexRGB());

		// 各扇形を繋ぐ線を描画
		if (i < 2)
		{
			DrawLine3D(originPoint.GetAsDxLibVector(), (originPoint + Vector3(0.0f, kFovVDistance, 0.0f)).GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
			DrawLine3D(fovLeftEdgePoint.GetAsDxLibVector(), (fovLeftEdgePoint + Vector3(0.0f, kFovVDistance, 0.0f)).GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
			DrawLine3D(fovRightEdgePoint.GetAsDxLibVector(), (fovRightEdgePoint + Vector3(0.0f, kFovVDistance, 0.0f)).GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
		}

		// 弧を描画
		constexpr float arc = Math::ToRadian(kFovHAngle / kDebugFOVQuolity);
		for (int j = 0; j < kDebugFOVQuolity; j++)
		{
			float rot0 = startRot + arc * j;
			Vector3 point0 = originPoint + Vector3(std::cos(rot0), 0.0f, -std::sin(rot0)) * kSearchRange;

			float rot1 = startRot + arc * (j + 1);
			Vector3 point1 = originPoint + Vector3(std::cos(rot1), 0.0f, -std::sin(rot1)) * kSearchRange;

			DrawLine3D(point0.GetAsDxLibVector(), point1.GetAsDxLibVector(), Color::yellow.GetAsHexRGB());
		}
	}
}
