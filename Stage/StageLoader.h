#pragma once

#include <string>
#include <memory>
#include <vector>

class GameObject;

namespace Stage
{
	class StageLoader
	{
	public:

		/// <summary>
		/// ステージデータを読み込んでオブジェクトを生成する
		/// </summary>
		static std::vector<std::unique_ptr<GameObject>> Load(const std::string& path);
	};
}
