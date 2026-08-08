#include "EffectAnimator.h"
#include <memory>
#include <string>
#include <EffekseerForDXLib.h>
#include "../GameObject.h"
#include "System/ResourceManager.h"
#include "System/TimeManager.h"
#include "System/Resource/Effect.h"

namespace
{
	constexpr float kFPS = 60.0f;
}

EffectAnimator::EffectAnimator(GameObject* owner, const std::string& path) :
	mEffectPlayHandle(-1),
	mOwner(owner),
	mResource(nullptr)
{
	mResource = ResourceManager::GetInstance().GetResource<Resource::Effect>(path);
}

EffectAnimator::~EffectAnimator()
{
	if (mEffectPlayHandle != -1) StopEffekseer3DEffect(mEffectPlayHandle);
}

void EffectAnimator::Update()
{
	if (!mResource) return;
	if (!IsPlaying()) return;

	// Ä¶‚ªI—¹‚µ‚Ä‚¢‚½‚ç
	if (IsEffekseer3DEffectPlaying(mEffectPlayHandle) == -1)
	{
		mEffectPlayHandle = -1;
		return;
	}

	Vector3 worldPos = mOwner->GetTransform().CalculateWorldPosition();
	SetPosPlayingEffekseer3DEffect(mEffectPlayHandle, worldPos.x, worldPos.y, worldPos.z);
}

void EffectAnimator::Play()
{
	if (!mResource) return;

	if (IsPlaying()) return;

	mEffectPlayHandle = PlayEffekseer3DEffect(mResource->GetHandle());
}

void EffectAnimator::Stop()
{
	// Ä¶‚µ‚Ä‚¢‚È‚¢‚È‚ç‘ŠúƒŠƒ^[ƒ“
	if (!IsPlaying()) return;
	
	StopEffekseer3DEffect(mEffectPlayHandle);

	mEffectPlayHandle = -1;
}
