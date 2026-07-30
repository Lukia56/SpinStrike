#pragma once

#include "../SceneBase.h"

class StageObject;

class SceneStageTest : public SceneBase
{
public:

	SceneStageTest();
	~SceneStageTest() = default;

	void Init() override;

	std::unique_ptr<SceneBase> Update() override;

	void DebugDraw() override;

private:

	StageObject* mStageObject;

	bool mIsStartTransition;
};
