#pragma once

#include "ModelAnimator.h"

class GameObject;

class TornadoModelAnimator :public ModelAnimator
{
public:

	TornadoModelAnimator(GameObject* tornado, ModelRenderer* renderer, float fps = TimeManager::kFPS);
	~TornadoModelAnimator() = default;

	void Update() override;

private:

	GameObject* mTornado;
};
