#pragma once

#include "EnemyActionBase.h"

class EnemyActionWait : public EnemyActionBase
{
public:

	struct Arguments
	{
		float time;
	};

	EnemyActionWait(const Arguments& arguments);
	~EnemyActionWait() = default;

	void Setup() override;

	bool OnExecute(Enemy& enemy, int& actionIndex) override;

private:

	const float mWaitTime;

	float mWaitTimer;
};
