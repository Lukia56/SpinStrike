#pragma once

#include "EnemyActionBase.h"

class EnemyActionTest : public EnemyActionBase
{
public:

	EnemyActionTest() = default;
	~EnemyActionTest() = default;

	bool OnExecute(Enemy& enemy, int& actionIndex) override;
};
