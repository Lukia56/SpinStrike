#pragma once

#include "../SceneBase.h"

class EffectTest;

class SceneEffekseerTest : public SceneBase
{
public:

	SceneEffekseerTest();
	~SceneEffekseerTest() = default;

	void Init() override;

	std::unique_ptr<SceneBase> Update() override;
};
