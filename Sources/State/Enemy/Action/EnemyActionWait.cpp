#include "EnemyActionWait.h"
#include "System/TimeManager.h"

EnemyActionWait::EnemyActionWait(const Arguments& arguments) :
	mWaitTime(arguments.time),
	mWaitTimer(0.0f)
{
}

void EnemyActionWait::Setup()
{
	mWaitTimer = mWaitTime;
}

bool EnemyActionWait::OnExecute(Enemy& enemy, int& actionIndex)
{
	mWaitTimer -= TimeManager::GetDeltaTime();

	if (mWaitTimer < 0.0f) return false;

	return true;
}
