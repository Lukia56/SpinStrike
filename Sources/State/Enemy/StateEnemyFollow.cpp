#include "StateEnemyFollow.h"
#include "StateEnemyPatrolling.h"
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

std::unique_ptr<IState<Enemy>> StateEnemyFollow::Update(Enemy& owner)
{
	Transform* transform = owner.GetTransform();

	Vector3 vecToPlayer = owner.GetPlayerTransform()->CalculateWorldPosition() - transform->CalculateWorldPosition();

	if (vecToPlayer != Vector3::Zero)
	{
		if (vecToPlayer.GetSqLength() > Math::Sqr(kLostRange))
		{
			owner.SetVelocity(Vector3::Zero);
			return std::make_unique<StateEnemyPatrolling>();
		}

		Vector3 ToPlayerNorm = vecToPlayer.GetNormalize();
		ToPlayerNorm.y = 0.0f;

		owner.SetVelocity(ToPlayerNorm * kMoveSpeed);
	}

	return nullptr;
}

void StateEnemyFollow::Exit(Enemy& owner)
{
}
