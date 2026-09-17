#include "StateEnemyFollow.h"
#include "../StateContext.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"
#include "World/Character/Enemy.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;

	// Ž‹–ì‚©‚çŠO‚ê‚ÄŒ©Ž¸‚¤‚Ü‚Å‚ÌŽžŠÔ
	constexpr float kLostTime = 3.0f;
}

StateEnemyFollow::StateEnemyFollow() :
	mLostTimer(0.0f)
{
}

void StateEnemyFollow::Enter(Enemy& enemy)
{
	mLostTimer = 0.0f;
}

void StateEnemyFollow::Update(Enemy& enemy, StateContext<Enemy>& context)
{
	Transform* transform = enemy.GetTransform();

	Vector3 toPlayerVec = enemy.GetPlayerTransform()->CalculateWorldPosition() - transform->CalculateWorldPosition();
	if (toPlayerVec == Vector3::Zero) return;
	
	CountLostTimer(enemy);

	if (IsLostPlayer())
	{
		context.PopState();
		return;
	}

	Vector3 toPlayerNorm = toPlayerVec.GetNormalize();
	toPlayerNorm.y = 0.0f;

	enemy.SetTargetYaw(std::atan2(toPlayerNorm.x, -toPlayerNorm.z));
	enemy.SetVelocity(toPlayerNorm * kMoveSpeed);
}

void StateEnemyFollow::Exit(Enemy& enemy)
{
	enemy.SetVelocity(Vector3::Zero);
}

void StateEnemyFollow::CountLostTimer(const Enemy& enemy)
{
	if (enemy.IsFoundPlayer())
	{
		mLostTimer = 0.0f;
		return;
	}

	mLostTimer += TimeManager::GetDeltaTime();
}

bool StateEnemyFollow::IsLostPlayer() const
{
	return mLostTimer > kLostTime;
}
