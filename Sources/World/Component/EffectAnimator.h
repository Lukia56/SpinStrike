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

private:

	void Stop();

	bool IsPlaying() const { return mEffectPlayHandle != -1; }

private:

	int mEffectPlayHandle;

	GameObject* mOwner;

	Resource* mResource;
};
