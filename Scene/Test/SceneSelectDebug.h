#pragma once

#include "../SceneBase.h"
#include <functional>
#include <string>
#include <vector>

class SceneSelectDebug : public SceneBase
{
public:

	struct SceneInfo
	{
		std::string name;
		std::function<std::unique_ptr<SceneBase>()> createSceneFunc;
	};

public:

	SceneSelectDebug();
	~SceneSelectDebug() = default;

	void Init() override;

	std::unique_ptr<SceneBase> Update() override;

	void DebugDraw();

private:

	int mCursorPos;

	std::vector<SceneInfo> mSceneList;
};
