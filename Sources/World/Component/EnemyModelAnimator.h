#pragma once

#include "ModelAnimator.h"
#include "../Character/EnemyAnimation.h"

struct AnimationParam;

/// <summary>
/// 敵のアニメーション処理・遷移を行う
/// </summary>
class EnemyModelAnimator : public ModelAnimator
{
public:

	EnemyModelAnimator(const std::vector<AnimationParam>& animParams, ModelRenderer* renderer, float fps = TimeManager::kFPS);
	~EnemyModelAnimator() = default;

	void Update() override;

public:

	void SetNextAnimation(EnemyAnimation next) { mNextAnimation = next; }

private:

	EnemyAnimation mCurrentAnimation;

	EnemyAnimation mNextAnimation;

	const std::vector<AnimationParam>& mAnimationParams;
};
