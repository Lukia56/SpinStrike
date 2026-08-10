#pragma once

#include "../SceneBase.h"

class SceneUITest : public SceneBase
{
public:

	SceneUITest();
	~SceneUITest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;
};
