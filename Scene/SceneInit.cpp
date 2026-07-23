#include "SceneInit.h"
#include "Test/SceneSelectDebug.h"

void SceneInit::Init()
{
}

std::unique_ptr<SceneBase> SceneInit::Update()
{
	return std::make_unique<SceneSelectDebug>();
}
