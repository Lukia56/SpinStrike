#include "StateEnemyPatrollingInterpreter.h"
#include <vector>
#include "../StateContext.h"
#include "Action/EnemyActionBase.h"
#include "Param/Param.h"

StateEnemyPatrollingInterpreter::StateEnemyPatrollingInterpreter(std::vector<WaypointActionData> actionData) :
	mActionIndex(-1),
	mActionDataIndex(-1),
	mActionData(std::move(actionData))
{
}

void StateEnemyPatrollingInterpreter::Enter(Enemy& owner)
{
	mActionIndex = 0;

	mActionDataIndex = -1;
	for (int i = 0; i < mActionData.size(); i++)
	{
		if (mActionData[i].waypointID != owner.GetCurrentWaypointID()) continue;

		mActionDataIndex = i;
	}
}

void StateEnemyPatrollingInterpreter::Update(Enemy& owner, StateContext<Enemy>& context)
{
	if (mActionDataIndex == -1)
	{
		context.PopState();
		return;
	}

	auto& actions = mActionData[mActionDataIndex].actions;

	// アクションインデクスは戻る場合があるためwhileループ
	while (mActionIndex < actions.size())
	{
		bool isEndFrame = actions[mActionIndex]->Execute(owner, mActionIndex);

		if (isEndFrame) break;

		mActionIndex++;
	}

	if (mActionIndex >= actions.size())
	{
		context.PopState();
		return;
	}
}

void StateEnemyPatrollingInterpreter::Exit(Enemy& owner)
{
}
