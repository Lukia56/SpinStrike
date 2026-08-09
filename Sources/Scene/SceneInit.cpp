#include "SceneInit.h"
#include "Test/SceneSelectDebug.h"

void SceneInit::OnInit()
{
}

std::unique_ptr<SceneBase> SceneInit::OnUpdate()
{
	return std::make_unique<SceneSelectDebug>();
}
