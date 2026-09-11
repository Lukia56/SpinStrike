#include "StateEnemyFollow.h"
#include "StateEnemyPatrolling.h"
#include "../StateContext.h"
#include "World/Character/Enemy.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;

	constexpr float kLostRange = 500.0f;
}

StateEnemyFollow::StateEnemyFollow()
{
}

void StateEnemyFollow::Enter(Enemy& owner)
{
}

void StateEnemyFollow::Update(Enemy& owner, StateContext<Enemy>& context)
{
	Transform* transform = owner.GetTransform();

	Vector3 vecToPlayer = owner.GetPlayerTransform()->CalculateWorldPosition() - transform->CalculateWorldPosition();

	if (vecToPlayer != Vector3::Zero)
	{
		if (vecToPlayer.GetSqLength() > Math::Sqr(kLostRange))
		{
			owner.SetVelocity(Vector3::Zero);
			context.ChangeState<StateEnemyPatrolling>();
			return;
		}

		Vector3 ToPlayerNorm = vecToPlayer.GetNormalize();
		ToPlayerNorm.y = 0.0f;

		owner.SetVelocity(ToPlayerNorm * kMoveSpeed);
	}
}

void StateEnemyFollow::Exit(Enemy& owner)
{
}
