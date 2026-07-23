#pragma once

#include "System/TimeManager.h"

struct AnimationParam;
class ModelRenderer;

class Animator
{
public:

	Animator(ModelRenderer* renderer, float fps = TimeManager::kFPS);
	~Animator();

	void Update();

	void Play(const AnimationParam& param);

public:

	int GetAnimIndex() const { return mAnimIndex; }

	bool IsPlaying() const { return mIsPlaying; }

	bool IsForcePlay() const { return mIsForcePlay; }

	void SetPlaySpeed(const float speed) { mPlaySpeed = speed; }

private:

	bool IsPlayingOneShotAnim() const;

	bool IsPlayingSameAnim(int animIndex) const;

private:

	/// <summary>
	/// 現在アタッチしているアニメーションアタッチ番号
	/// </summary>
	int mAttachIndex;

	/// <summary>
	/// 現在再生しているアニメーション番号
	/// </summary>
	int mAnimIndex;

	float mTime;

	float mTotalTime;

	bool mIsPlaying;

	bool mIsLoop;

	bool mIsForcePlay;

	float mPlaySpeed;

	float mFPS;

	ModelRenderer* mRenderer;
};
