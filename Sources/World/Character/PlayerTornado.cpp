#include "PlayerTornado.h"
#include <imgui.h>
#include "PlayerBulletManager.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 300.0f, 100.0f, 300.0f };

	constexpr Vector3 kCollisionOffsetPos{ 0.0f, kCollisionSize.y / 2.0f, 0.0f };
}

PlayerTornado::PlayerTornado(PlayerBulletManager* bulletManager) :
	mPulledNum(0),
	mCollider(nullptr),
	mBulletManager(bulletManager)
{
	SetTag(Tag::Tornado);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kCollisionSize, kCollisionOffsetPos),
		this,
		Collision::Tag::Body,
		false
	);
}

PlayerTornado::~PlayerTornado()
{
}

void PlayerTornado::Init()
{
}

void PlayerTornado::Finalize()
{
}

void PlayerTornado::Update()
{
	mCollider->GetShape()->SetPosition(mTransform->CalculateWorldPosition());
}

void PlayerTornado::Draw()
{
}

void PlayerTornado::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();

	if (ImGui::Begin("Player"))
	{
		ImGui::Text("===== Tornado =====");

		ImGui::Text("PulledCount = %d", mPulledNum);

		ImGui::End();
	}
}

void PlayerTornado::CreateBullet(const Vector3& moveVec)
{
	if (mPulledNum <= 0) return;

	mBulletManager->CreateBullet(mTransform->CalculateWorldPosition(), moveVec);

	mPulledNum = 0;
}

void PlayerTornado::SetActive(bool flag)
{
	if (IsActive() == flag) return;

	GameObject::SetActive(flag);
	
	if (flag)
	{
		mCollider->Enable();
	}
	else
	{
		mCollider->Disable();
	}
}
