#pragma once

#include "../SceneBase.h"

class SceneModelAnimTest : public SceneBase
{
public:

	SceneModelAnimTest();
	~SceneModelAnimTest() = default;

	void OnInit() override;
	std::unique_ptr<SceneBase> OnUpdate() override;
};
