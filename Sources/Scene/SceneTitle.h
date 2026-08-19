#pragma once

#include "SceneBase.h"

namespace UI
{
	class UIManager;
}

class SceneTitle : public SceneBase
{
public:

	SceneTitle();
	~SceneTitle() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	UI::UIManager* mUIManager;
};
