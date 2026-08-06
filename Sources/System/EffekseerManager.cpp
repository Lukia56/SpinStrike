#include "EffekseerManager.h"
#include <EffekseerForDXLib.h>

namespace
{
	constexpr int kMaxParticle = 8000;
}

bool EffekseerManager::Initialize()
{
	if (Effekseer_Init(kMaxParticle) == -1) return false;

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	return true;
}

void EffekseerManager::Finalize()
{
	Effkseer_End();
}

void EffekseerManager::Update()
{
	UpdateEffekseer3D();
}

void EffekseerManager::Draw()
{
	DrawEffekseer3D();
}
