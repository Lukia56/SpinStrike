#pragma once

#include "../SceneBase.h"

namespace UI
{
	class UIManager;
}

class SceneMenuUITest : public SceneBase
{
public:

	SceneMenuUITest();
	~SceneMenuUITest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	UI::UIManager* mUIManager;
};
