#include "StateEnemyAttack.h"
#include "StateEnemyFollow.h"
#include "../StateContext.h"
#include "System/TimeManager.h"
#include "World/Character/Enemy.h"

namespace
{
	constexpr float kAttackCooldownTime = 1.5f;
	constexpr float kAttackDuration = 0.5f;

	constexpr float kAttackColliderOffset = 50.0f;
}

StateEnemyAttack::StateEnemyAttack() :
	mAttackCooldownTimer(0.0f)
{
}

void StateEnemyAttack::Enter(Enemy& enemy)
{
	Transform* transform = enemy.GetTransform();

	Vector3 toPlayerVec = enemy.GetPlayerTransform()->CalculateWorldPosition() - transform->CalculateWorldPosition();
	toPlayerVec.y = 0.0f;
	if (toPlayerVec == Vector3::Zero) return;

	Vector3 toPlayerNorm = toPlayerVec.GetNormalize();

	float yaw = std::atan2(toPlayerNorm.x, -toPlayerNorm.z);
	enemy.SetTargetYaw(yaw);

	enemy.StartAttack(kAttackDuration, toPlayerNorm * kAttackColliderOffset);

	mAttackCooldownTimer = kAttackCooldownTime;
}

void StateEnemyAttack::Update(Enemy& enemy, StateContext<Enemy>& context)
{
	mAttackCooldownTimer -= TimeManager::GetDeltaTime();

	if (mAttackCooldownTimer < 0.0f)
	{
		context.ChangeState<StateEnemyFollow>();
		return;
	}
}

void StateEnemyAttack::Exit(Enemy& enemy)
{
}
