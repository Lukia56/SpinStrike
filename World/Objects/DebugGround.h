#pragma once

#include "../GameObject.h"

/// <summary>
/// デバッグ用の格子状の地面を描画する
/// </summary>
class DebugGround : public GameObject
{
public:

	DebugGround() = default;
	~DebugGround() = default;

	void Init() override {};
	void Update() override {};

	void Draw() override;
};
