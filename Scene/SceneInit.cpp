#include "SceneInit.h"
#include "SceneTest.h"

void SceneInit::Init()
{
}

void SceneInit::Finalize()
{
}

std::unique_ptr<SceneBase> SceneInit::Update()
{
	return std::make_unique<SceneTest>();
}
