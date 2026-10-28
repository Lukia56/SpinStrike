#pragma once

#include "../SceneBase.h"

class Player;
class Enemy;
namespace Observer
{
	class GameOverObserver;
	class GoalObserver;
}

class SceneStageTest : public SceneBase
{
public:

	SceneStageTest();
	~SceneStageTest();

	void OnInit() override;
	void OnFinalize() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	Enemy* mEnemy;

	std::unique_ptr<Observer::GameOverObserver> mGameOverObserver;
	std::unique_ptr<Observer::GoalObserver> mGoalObserver;
};
