#include "PlayerBulletManager.h"
#include "PlayerBullet.h"
#include "../Other/RootObject.h"

PlayerBulletManager::PlayerBulletManager(int maxNum) :
	mActiveBulletRoot(nullptr),
	mPoolBulletRoot(nullptr)
{
	mPoolBulletRoot = CreateToChild<RootObject>();
	mPoolBulletRoot->SetActive(false);

	for (int i = 0; i < maxNum; i++)
	{
		PlayerBullet* bullet = mPoolBulletRoot->CreateToChild<PlayerBullet>();
		mPoolBullets.emplace(bullet);
	}
}

void PlayerBulletManager::Init()
{
	mActiveBulletRoot = CreateToChild<RootObject>();
}

void PlayerBulletManager::Update()
{
	// 再生が終了したインスタンスを削除する
	for (auto iter = mActiveBullets.begin(); iter != mActiveBullets.end();)
	{
		PlayerBullet* bullet = *iter;

		if (bullet->GetDestroyTimer() > 0.0f)
		{
			iter++;
			continue;
		}

		// プールに移動させる
		bullet->GetTransform()->ChangeParent(mPoolBulletRoot->GetTransform());

		mPoolBullets.emplace(bullet);
		iter = mActiveBullets.erase(iter);
	}
}

void PlayerBulletManager::CreateBullet(const Vector3& pos, const Vector3& moveVec)
{
	// プールから取り出す
	PlayerBullet* bullet = mPoolBullets.top();

	bullet->GetTransform()->ChangeParent(mActiveBulletRoot->GetTransform());
	bullet->Setup(pos, moveVec);

	mPoolBullets.pop();
	mActiveBullets.emplace_back(bullet);
}
