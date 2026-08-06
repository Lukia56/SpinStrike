#include "EffectAnimator.h"
#include <string>
#include <EffekseerForDXLib.h>
#include "../GameObject.h"
#include "System/ResourceManager.h"
#include "System/TimeManager.h"
#include "System/Resource/Resource.h"

namespace
{
	constexpr float kFPS = 60.0f;
}

EffectAnimator::EffectAnimator(GameObject* owner, const std::string& path) :
	mEffectPlayHandle(-1),
	mIsPlaying(false),
	mOwner(owner),
	mResource(nullptr)
{
	mResource = ResourceManager::GetInstance().GetResource<Effect>(path);
}

EffectAnimator::~EffectAnimator()
{
	if (mEffectPlayHandle != -1) StopEffekseer3DEffect(mEffectPlayHandle);
}

void EffectAnimator::Update()
{
	if (!mResource) return;
	if (!mIsPlaying) return;

	// Ä¶‚ªI—¹‚µ‚Ä‚¢‚½‚ç
	if (IsEffekseer3DEffectPlaying(mEffectPlayHandle) == -1)
	{
		mIsPlaying = false;
		return;
	}

	Vector3 worldPos = mOwner->GetTransform().CalculateWorldPosition();
	SetPosPlayingEffekseer3DEffect(mEffectPlayHandle, worldPos.x, worldPos.y, worldPos.z);
}

void EffectAnimator::Play()
{
	if (!mResource) return;

	if (mEffectPlayHandle != -1) StopEffekseer3DEffect(mEffectPlayHandle);

	mEffectPlayHandle = PlayEffekseer3DEffect(mResource->GetHandle());

	mIsPlaying = true;
}
