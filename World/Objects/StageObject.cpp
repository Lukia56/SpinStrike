#include "StageObject.h"
#include "../Components/Collider3D.h"
#include "../Components/Rendering/ModelRenderer.h"
#include "Collision/Collision3D.h"
#include "Param/Param.h"

namespace
{
	const char* const kModelPath = "Resource\\Model\\";
}

StageObject::StageObject(const StageObjectParam& param, const std::string& modelPath) :
	mModel(nullptr),
	mCollider(nullptr)
{
	mTransform.localPosition = param.transform.position;
	mTransform.localRotation = param.transform.rotation;
	mTransform.localScale = param.transform.scale;

	mModel = std::make_unique<ModelRenderer>(this);
	mModel->Load(modelPath);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(param.bounds.size, param.bounds.offsetPos),
		this,
		Collision::Tag::Body
	);
	mCollider->GetShape()->SetPosition(mTransform.CalculateWorldPosition());
}

void StageObject::Init()
{
}

void StageObject::Update()
{
}

void StageObject::Draw()
{
	mModel->Draw();
}

void StageObject::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}
