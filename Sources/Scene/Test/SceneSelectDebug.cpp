#include "SceneSelectDebug.h"
#include <DxLib.h>
#include "SceneTest.h"
#include "SceneCollisionDebug.h"
#include "SceneStageTest.h"
#include "System/InputManager.h"
#include "Utility/Color.h"

SceneSelectDebug::SceneSelectDebug() :
	mCursorPos(0)
{
}

void SceneSelectDebug::Init()
{
	SceneInfo info;

	info.name = "Test1";
	info.createSceneFunc = []() { return std::make_unique<SceneTest>(); };
	mSceneList.emplace_back(info);

	info.name = "CollisionDebug";
	info.createSceneFunc = []() { return std::make_unique<SceneCollisionDebug>(); };
	mSceneList.emplace_back(info);

	info.name = "StageDebug";
	info.createSceneFunc = []() { return std::make_unique<SceneStageTest>(); };
	mSceneList.emplace_back(info);
}

std::unique_ptr<SceneBase> SceneSelectDebug::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Up)) mCursorPos--;
	if (InputManager::GetInstance().IsPressed(Input::Action::Down)) mCursorPos++;
	int listSize = static_cast<int>(mSceneList.size());
	mCursorPos = (mCursorPos + listSize) % listSize;

	if (InputManager::GetInstance().IsPressed(Input::Action::Submit))
	{
		return mSceneList[mCursorPos].createSceneFunc();
	}

	return nullptr;
}

void SceneSelectDebug::DebugDraw()
{
	DrawString(200, 30, "Select a Scene", Color::white.GetAsHexRGB());

	for (int i = 0; i < static_cast<int>(mSceneList.size()); i++)
	{
		DrawString(240, 60 + i * 20, mSceneList[i].name.c_str(), Color::white.GetAsHexRGB());

		if (mCursorPos == i)
		{
			DrawString(220, 60 + i * 20, ">", Color::white.GetAsHexRGB());
		}
	}
}
