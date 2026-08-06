#include "EffectTest.h"
#include <imgui.h>
#include "../Component/EffectAnimator.h"
#include "System/InputManager.h"

namespace
{
	const char* const kEffectPath = "Resources\\Effect\\Tornade.efk";
}

EffectTest::EffectTest() :
	mEffectAnimator(nullptr)
{
}

void EffectTest::Init()
{
	mEffectAnimator = std::make_unique<EffectAnimator>(this, kEffectPath);
}

void EffectTest::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Submit))
	{
		mEffectAnimator->Play();
	}

	mEffectAnimator->Update();
}
