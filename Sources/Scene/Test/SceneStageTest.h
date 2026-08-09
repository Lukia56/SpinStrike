#pragma once

#include "../SceneBase.h"

class Player;

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
};
