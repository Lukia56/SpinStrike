#pragma once

#include <string>

class GameObject;
class Resource;

/// <summary>
/// エフェクトの再生を行う
/// </summary>
class EffectAnimator
{
public:

	EffectAnimator(GameObject* owner, const std::string& path);
	~EffectAnimator();

	/// <summary>
	/// 位置設定や再生状態の処理を行う
	/// </summary>
	void Update();

	void Play();

public:

	bool IsPlaying() const { return mIsPlaying; }

private:

	int mEffectPlayHandle;

	bool mIsPlaying;

	GameObject* mOwner;

	Resource* mResource;
};
