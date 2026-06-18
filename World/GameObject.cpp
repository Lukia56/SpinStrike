#include "GameObject.h"
#include <cassert>
#include <memory>
#include <vector>
#include "Components/Transform.h"

GameObject::GameObject() :
	mTransform(this),
	mIsCalledDestroy(false),
	mIsActive(true)
{
}

GameObject::~GameObject()
{
}

bool GameObject::CheckDestroy()
{
	// 自身のイテレータを取得してコンテナから削除する
	if (mIsCalledDestroy && mTransform.GetParent())
	{
		// 終了処理を呼ぶ
		Finalize();

		mTransform.ChangeParent(nullptr);

		return true;
	}

	// 子オブジェクトについて再帰
	for (int i = 0; i < mTransform.GetChildren().size();)
	{
		if (mTransform.GetChildren()[i]->CheckDestroy()) continue;

		i++;
	}

	return false;
}

void GameObject::Destroy(GameObject* deleteTarget)
{
	if (deleteTarget == nullptr)
	{
		assert(false && "GameObject // 削除しようとしたゲームオブジェクトはnullptrです");
		return;
	}
	deleteTarget->mIsCalledDestroy = true;
}
