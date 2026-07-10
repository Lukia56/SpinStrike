#include "Crate.h"
#include "../Characters/PlayerTornado.h"
#include "../Components/Collider3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "Collision/Collision3D.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"
#include "Utility/Random.h"

namespace
{
	constexpr Vector3 kSize{ 0.5f, 0.5f, 0.5f };

	constexpr Vector3 kCollisionSize{ 100.0f, 100.0f, 100.0f };

	constexpr float kEnduranceTime = 0.5f;

	constexpr float kShakeRange = 10.0f;

	const char* const kModelPath = "Resource\\Model\\Cube_Crate.mv1";
}

Crate::Crate() :
	mEnduranceTimer(0.0f),
	mIsHitTornado(false),
	mModel(nullptr)
{
	SetTag(Tag::Terrain);

	mModel = std::make_unique<ModelRenderer>(this);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(Vector3::Zero, kCollisionSize),
		this,
		Collider3D::Tag::Body
	);

	mTransform.localScale = kSize;
}

Crate::~Crate()
{
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

	mCollider->GetShape()->SetPosition(mTransform.CalculateWorldPosition());
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
