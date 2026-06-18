#pragma once

#include "SceneBase.h"

/// <summary>
/// 初期化シーン
/// 今は最初のシーンへの遷移のみ行う
/// </summary>
class SceneInit :  public SceneBase
{
public:

	SceneInit() = default;
	~SceneInit() = default;

	void Init() override;
	void Finalize() override;

	/// <returns>次のシーンのポインタ</returns>
	std::unique_ptr<SceneBase> Update() override;
};
