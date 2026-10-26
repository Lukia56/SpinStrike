#include "StateEnemyDamage.h"
#include "StateEnemyFollow.h"
#include "../StateContext.h"
#include "System/TimeManager.h"
#include "World/Character/Enemy.h"

namespace
{
	constexpr float kStunTime = 0.5f;

	constexpr int kDamage = 1;

	constexpr float kKnockbackForce = 10.0f;
}

StateEnemyDamage::StateEnemyDamage() :
	mStunTimer(0.0f)
{
}

void StateEnemyDamage::Enter(Enemy& enemy)
{
	mStunTimer = kStunTime;

	enemy.Damage(kDamage);
	enemy.SetInvincible(true);

	// プレイヤーへ向かせる
	Transform* transform = enemy.GetTransform();

	Vector3 toPlayerVec = enemy.GetPlayerTransform()->CalculateWorldPosition() - transform->CalculateWorldPosition();
	toPlayerVec.y = 0.0f;
	if (toPlayerVec == Vector3::Zero) return;

	Vector3 toPlayerNorm = toPlayerVec.GetNormalize();

	float yaw = std::atan2(toPlayerNorm.x, -toPlayerNorm.z);
	transform->localRotation.y = yaw;
	enemy.SetTargetYaw(yaw);

	// ノックバック
	enemy.AddKnockbackPush(toPlayerNorm * -kKnockbackForce);
}

void StateEnemyDamage::Update(Enemy& enemy, StateContext<Enemy>& context)
{
	mStunTimer -= TimeManager::GetDeltaTime();

	if (mStunTimer < 0.0f)
	{
		context.ChangeState<StateEnemyFollow>();
		return;
	}
}

void StateEnemyDamage::Exit(Enemy& enemy)
{
	enemy.SetInvincible(false);
}
