#include "PlayerTornado.h"
#include <imgui.h>
#include "../Components/Collision3D.h"
#include "System/CollisionManager.h"

namespace
{
	constexpr Vector3 kCollisionSize{ 300.0f, 100.0f, 300.0f };

	constexpr Vector3 kCollisionOffsetPos{ 0.0f, kCollisionSize.y / 2.0f, 0.0f };
}

PlayerTornado::PlayerTornado() :
	mIsSpinning(false),
	mPulledNum(0),
	mCollider(nullptr)
{
	mCollider = std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize);
}

PlayerTornado::~PlayerTornado()
{
	CollisionManager::GetInstance().Unregister(mCollider.get());
}

void PlayerTornado::Init()
{
}

void PlayerTornado::Finalize()
{
}

void PlayerTornado::Update()
{
	mCollider->SetPosition(mTransform.CalculateWorldPosition() + kCollisionOffsetPos);
}

void PlayerTornado::Draw()
{
}

void PlayerTornado::DebugDraw()
{
	if (mIsSpinning) mCollider->DebugDraw();

	using namespace ImGui;
	if (Begin("Player"))
	{
		Text("===== Tornade =====");

		Text("PulledCount = %d", mPulledNum);

		End();
	}
}

void PlayerTornado::SetSpinningFlag(const bool flag)
{
	if (mIsSpinning == flag) return;

	mIsSpinning = flag;
	
	if (flag)
	{
		CollisionManager::GetInstance().Register(this, mCollider.get(), Collision::Tag::Tornade);
	}
	else
	{
		mPulledNum = 0;

		CollisionManager::GetInstance().Unregister(mCollider.get());
	}
}
