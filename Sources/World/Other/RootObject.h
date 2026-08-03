#pragma once

#include "../GameObject.h"

/// <summary>
/// オブジェクト生成のルート用の空のゲームオブジェクト
/// </summary>
class RootObject : public GameObject
{
public:

	void Init() override {};
	void Update() override {};
};
