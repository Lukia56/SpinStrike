#pragma once

#include "../SceneBase.h"

class StageObject;

class SceneLoadStageTest : public SceneBase
{
public:

	SceneLoadStageTest();
	~SceneLoadStageTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

	void OnDebugDraw() override;

private:

	bool mIsStartTransition;
};
