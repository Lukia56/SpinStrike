#include "EnemyActionBase.h"

bool EnemyActionBase::Execute(Enemy& enemy, int& actionIndex)
{
	bool isEndFrame = OnExecute(enemy, actionIndex);

	// 次のアクションを実行するなら初期化する
	if (!isEndFrame) Setup();

	return isEndFrame;
}
