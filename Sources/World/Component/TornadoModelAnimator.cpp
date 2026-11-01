#include "TornadoModelAnimator.h"
#include "Rendering/ModelRenderer.h"
#include "Utility/Math.h"
#include "World/GameObject.h"

namespace
{
	constexpr Vector3 kSpinRotate{ 0.0f, Math::ToRadian(20.0f), 0.0f };
}

TornadoModelAnimator::TornadoModelAnimator(GameObject* tornado, ModelRenderer* renderer, float fps) :
	ModelAnimator(renderer, fps),
	mTornado(tornado)
{
}

void TornadoModelAnimator::Update()
{
	GetModelRenderer()->Rotate(kSpinRotate);

	ModelAnimator::Update();
}
