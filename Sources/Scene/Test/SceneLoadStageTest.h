#pragma once

#include "../SceneBase.h"

class StageObject;

class SceneLoadStageTest : public SceneBase
{
public:

	SceneLoadStageTest();
	~SceneLoadStageTest() = default;

	void Init() override;

	std::unique_ptr<SceneBase> Update() override;

	void DebugDraw() override;

private:

	bool mIsStartTransition;
};
