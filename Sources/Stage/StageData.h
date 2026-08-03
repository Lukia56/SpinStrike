#pragma once

#include "Param/Param.h"

namespace Stage
{
	/// <summary>
	/// ステージの配置オブジェクトのパラメータをまとめた構造体
	/// </summary>
	struct StageData
	{
		std::vector<StageObjectParam> objects;
	};
}
