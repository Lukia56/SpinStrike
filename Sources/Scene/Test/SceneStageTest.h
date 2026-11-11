#pragma once

#include "../SceneBase.h"

class Player;
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

	std::unique_ptr<Observer::GameOverObserver> mGameOverObserver;
	std::unique_ptr<Observer::GoalObserver> mGoalObserver;
};
