#include "EnemyModelAnimator.h"
#include "Param/Param.h"

EnemyModelAnimator::EnemyModelAnimator(const std::vector<AnimationParam>& animParams, ModelRenderer* renderer, float fps) :
	ModelAnimator(renderer, fps),
	mCurrentAnimation(EnemyAnimation::Idle),
	mNextAnimation(EnemyAnimation::Idle),
	mAnimationParams(animParams)
{
}

void EnemyModelAnimator::Update()
{
	// アニメーション切り替え
	if (mCurrentAnimation != mNextAnimation)
	{
		if (Play(mAnimationParams[static_cast<size_t>(mNextAnimation)]))
		{
			mCurrentAnimation = mNextAnimation;
		}
	}

	ModelAnimator::Update();

	mNextAnimation = EnemyAnimation::Idle;
}
