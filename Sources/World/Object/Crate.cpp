#include "Crate.h"
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "Collision/Collision3D.h"
#include "System/TimeManager.h"
#include "System/Resource/ResourceBase.h"
#include "Utility/Random.h"

namespace
{
	constexpr Vector3 kSize{ 0.5f, 0.5f, 0.5f };

	constexpr Vector3 kCollisionSize{ 100.0f, 100.0f, 100.0f };

	constexpr float kEnduranceTime = 0.5f;

	constexpr float kShakeRange = 10.0f;

	const char* const kModelPath = "Resources\\Model\\Cube_Crate.mv1";
}

Crate::Crate() :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mModel(nullptr),
	mCollider(nullptr)
{
	mModel = std::make_unique<ModelRenderer>(this, nullptr);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kCollisionSize),
		this,
		Collision::Tag::Body
	);
}

Crate::Crate(std::shared_ptr<Resource::ResourceBase> model) :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mModel(nullptr),
	mCollider(nullptr)
{
	mModel = std::make_unique<ModelRenderer>(this, model);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kCollisionSize),
		this,
		Collision::Tag::Body
	);
}

Crate::~Crate()
{
}

void Crate::Init()
{
	SetTag(Tag::Terrain);

	mTransform->localScale = kSize;
}

void Crate::Finalize()
{
}

void Crate::Update()
{
	if (!mIsHitTornado)
	{
		mEnduranceTimer = 0.0f;
		mModel->SetOffsetPos(Vector3::Zero);
	}
	else
	{
		mModel->SetOffsetPos(Vector3(Random::Range(-kShakeRange, kShakeRange), Random::Range(-kShakeRange, kShakeRange), Random::Range(-kShakeRange, kShakeRange)));
	}
	mIsHitTornado = false;

	mCollider->GetShape()->SetPosition(mTransform->CalculateWorldPosition());
}

void Crate::Draw()
{
	mModel->Draw();

	mCollider->GetShape()->DebugDraw();
}

void Crate::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (oppCollider->GetOwner()->GetTag() != Tag::Tornado) return;

	mEnduranceTimer += TimeManager::GetDeltaTime();

	mIsHitTornado = true;

	if (mEnduranceTimer > kEnduranceTime)
	{
		// タグがTornadoなのはPlayerTornado以外無い想定のためstatic_cast
		auto tornado = static_cast<PlayerTornado*>(oppCollider->GetOwner());

		tornado->AddPulledNum();

		Destroy(this);
	}
}
