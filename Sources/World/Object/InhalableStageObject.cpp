#include "InhalableStageObject.h"
#include "../Character/PlayerTornado.h"
#include "../Component/Collider3D.h"
#include "../Component/Rendering/ModelRenderer.h"

namespace
{
	constexpr Vector3 kColliderSize{ 100.0f, 100.0f, 100.0f };
}

InhalableStageObject::InhalableStageObject(const StageObjectParam& param, std::shared_ptr<Resource::ResourceBase> model) :
	StageObject(param, model)
{
}

void InhalableStageObject::Init()
{
	StageObject::Init();
}

void InhalableStageObject::Update()
{
	StageObject::Update();
}

void InhalableStageObject::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Tornado:
	{
		PlayerTornado* tornado = dynamic_cast<PlayerTornado*>(oppCollider->GetOwner());

		tornado->AddPulledNum();

		Destroy(this);
		break;
	}
	}
}
