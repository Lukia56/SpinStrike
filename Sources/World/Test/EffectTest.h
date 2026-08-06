#pragma once

#include "../GameObject.h"

class EffectAnimator;

class EffectTest : public GameObject
{
public:

	EffectTest();
	~EffectTest() = default;

	void Init() override;
	void Update() override;

private:

	std::unique_ptr<EffectAnimator> mEffectAnimator;
};
