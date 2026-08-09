#pragma once

#include "../SceneBase.h"

class EffectTest;

class SceneEffekseerTest : public SceneBase
{
public:

	SceneEffekseerTest();
	~SceneEffekseerTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;
};
