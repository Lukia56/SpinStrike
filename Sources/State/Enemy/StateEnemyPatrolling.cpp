#include "StateEnemyPatrolling.h"
#include "StateEnemyFollow.h"
#include "Utility/Math.h"
#include "World/Character/Enemy.h"

namespace
{
	constexpr float kSearchRange = 500.0f;
}

StateEnemyPatrolling::StateEnemyPatrolling()
{
}

void StateEnemyPatrolling::Enter(Enemy& owner)
{
}

std::unique_ptr<IState<Enemy>> StateEnemyPatrolling::Update(Enemy& owner)
{
	Transform* player = owner.GetPlayerTransform();
	Transform* enemy = owner.GetTransform();

	Vector3 vecToPlayer = player->CalculateWorldPosition() - enemy->CalculateWorldPosition();

	// プレイヤーが認識範囲にいるなら
	if (vecToPlayer.GetSqLength() <= Math::Sqr(kSearchRange))
	{
		return std::make_unique<StateEnemyFollow>();
	}

	return nullptr;
}

void StateEnemyPatrolling::Exit(Enemy& owner)
{
}
