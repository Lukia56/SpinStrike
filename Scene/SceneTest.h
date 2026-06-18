#pragma once

#include "SceneBase.h"

class Player;
class Crate;
class UI;

class SceneTest : public SceneBase
{
public:

	SceneTest();
	~SceneTest();

	void Init() override;
	void Finalize() override;

	std::unique_ptr<SceneBase> Update() override;

private:

	Player* mPlayer;
};
