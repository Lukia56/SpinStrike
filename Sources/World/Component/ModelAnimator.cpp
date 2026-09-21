#include "ModelAnimator.h"
#include <assert.h>
#include <DxLib.h>
#include "Param/Param.h"
#include "Rendering/ModelRenderer.h"
#include "System/TimeManager.h"

ModelAnimator::ModelAnimator(ModelRenderer* renderer, float fps) :
	mAttachIndex(-1),
	mAnimIndex(-1),
	mTime(0.0f),
	mTotalTime(0.0f),
	mIsPlaying(false),
	mIsLoop(false),
	mIsForcePlay(false),
	mPlaySpeed(1.0f),
	mFPS(fps),
	mRenderer(renderer)
{
}

ModelAnimator::~ModelAnimator()
{
}

void ModelAnimator::Update()
{
	if (!mRenderer) return;
	if (!mIsPlaying) return;

	MV1SetAttachAnimTime(mRenderer->GetModelHandle(), mAttachIndex, mTime);

	mTime += mPlaySpeed * mFPS * TimeManager::GetDeltaTime();
	if (mTime > mTotalTime)
	{
		if (mIsLoop)
		{
			mTime = 0.0f;
		}
		else
		{
			mTime = mTotalTime;

			mIsPlaying = false;
			mIsForcePlay = false;
		}
	}
}

void ModelAnimator::Play(const AnimationParam& param)
{
	if (!mRenderer)
	{
		assert(false && "ModelAnimator // モデルレンダラがnullのためアニメーションを更新できませんでした");
		return;
	}
	
	if (IsPlayingOneShotAnim()) return;
	if (IsPlayingSameAnim(param.animIndex)) return;

	int modelHandle = mRenderer->GetModelHandle();
	int animModelHandle = mRenderer->GetAnimModelHandle();
	
	if (mAttachIndex != -1) MV1DetachAnim(modelHandle, mAttachIndex);
	mAttachIndex = MV1AttachAnim(modelHandle, param.animIndex, animModelHandle, true);

	mAnimIndex = param.animIndex;

	mTime = 0.0f;
	mTotalTime = MV1GetAttachAnimTotalTime(modelHandle, mAttachIndex);

	mIsPlaying = true;
	mIsLoop = param.isLoop;

	// ループするならワンショットアニメーションにしない
	if (!mIsLoop) mIsForcePlay = param.isForcePlay;
}

bool ModelAnimator::IsPlayingOneShotAnim() const
{
	return mIsForcePlay && mIsPlaying;
}

bool ModelAnimator::IsPlayingSameAnim(int animIndex) const
{
	return mAnimIndex == animIndex && mIsPlaying;
}
