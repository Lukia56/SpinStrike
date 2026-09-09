#pragma once

#include "World/Character/Enemy.h"

/// <summary>
/// 敵のアクション単位の基底
/// </summary>
class EnemyActionBase
{
public:

	virtual ~EnemyActionBase() = default;

	/// <summary>
	/// アクションを実行する
	/// </summary>
	/// <returns>フレームを終了するかどうか</returns>
	bool Execute(Enemy& enemy, int& actionIndex);

	/// <summary>
	/// アクションが実行し終わり、次のアクションを実行しにいく際に初期化する
	/// </summary>
	virtual void Setup() {}

	virtual bool OnExecute(Enemy& enemy, int& actionIndex) = 0;
};
