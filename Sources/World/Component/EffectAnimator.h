#pragma once

#include <memory>
#include <string>

class GameObject;
namespace Resource
{
	class ResourceBase;
}

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

	std::shared_ptr<Resource::ResourceBase> mResource;
};
