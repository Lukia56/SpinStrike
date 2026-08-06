#pragma once

#include "../SceneBase.h"

class Player;

class SceneStageTest : public SceneBase
{
public:

	SceneStageTest();
	~SceneStageTest();

	void Init() override;
	void Finalize() override;

	std::unique_ptr<SceneBase> Update() override;

private:

	Player* mPlayer;
};
