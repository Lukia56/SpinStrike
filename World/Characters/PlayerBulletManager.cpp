#include "PlayerBulletManager.h"
#include "PlayerBullet.h"

PlayerBulletManager::PlayerBulletManager()
{
}

void PlayerBulletManager::Init()
{
}

void PlayerBulletManager::Update()
{
}

void PlayerBulletManager::CreateBullet(const Vector3& pos, const Vector3& moveVec)
{
	auto bullet = AddToChild<PlayerBullet>(moveVec);
	bullet->GetTransform().localPosition = pos - mTransform.CalculateWorldPosition();
}
