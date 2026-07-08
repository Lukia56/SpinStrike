#include "Crate.h"
#include "../Characters/PlayerTornado.h"
#include "../Components/Collision3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "System/CollisionManager.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

namespace
{
	constexpr Vector3 kSize{ 0.5f, 0.5f, 0.5f };

	constexpr Vector3 kCollisionSize{ 100.0f, 100.0f, 100.0f };

	constexpr float kEnduranceTime = 0.5f;

	const char* const kModelPath = "Resource\\Model\\Cube_Crate.mv1";
}

Crate::Crate() :
	mEnduranceTimer(0.0f),
	mModel(nullptr)
{
	mModel = std::make_unique<ModelRenderer>(this);

	mCollider = std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize);
	CollisionManager::GetInstance().Register(this, mCollider.get(), Collision::Tag::Terrain);

	mTransform.localScale = kSize;
}

Crate::~Crate()
{
	CollisionManager::GetInstance().Unregister(mCollider.get());
}

void Crate::Init()
{
	mModel->Load(kModelPath);
}

void Crate::Finalize()
{
}

void Crate::Update()
{
	if (mEnduranceTimer > 0.0f)
	{
		mModel
	}

	mCollider->SetPosition(mTransform.CalculateWorldPosition());
}

void Crate::Draw()
{
	mModel->Draw();

	mCollider->DebugDraw();
}

void Crate::OnCollision(GameObject* other, const Collision::Result& result, Collision::Tag tag)
{
	if (tag != Collision::Tag::Tornade) return;

	mEnduranceTimer += TimeManager::GetDeltaTime();

	if (mEnduranceTimer > 1.0f)
	{
		// タグがTornadeなのはPlayerTornade以外無い想定のためstatic_cast
		auto tornade = static_cast<PlayerTornado*>(other);

		tornade->AddPulledNum();

		Destroy(this);
	}
}
