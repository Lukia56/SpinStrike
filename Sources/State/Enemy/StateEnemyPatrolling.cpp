#include "StateEnemyPatrolling.h"
#include "StateEnemyFollow.h"
#include "../StateContext.h"
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

void StateEnemyPatrolling::Update(Enemy& owner, StateContext<Enemy>& context)
{
	Transform* player = owner.GetPlayerTransform();
	Transform* enemy = owner.GetTransform();

	Vector3 vecToPlayer = player->CalculateWorldPosition() - enemy->CalculateWorldPosition();

	// プレイヤーが認識範囲にいるなら
	if (vecToPlayer.GetSqLength() <= Math::Sqr(kSearchRange))
	{
		context.ChangeState<StateEnemyFollow>();
		return;
	}
}

void StateEnemyPatrolling::Exit(Enemy& owner)
{
}
