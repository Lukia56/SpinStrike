#pragma once

#include <string>
#include <memory>
#include <vector>

class GameObject;

namespace Stage
{
	/// <summary>
	/// ステージのデータを読み込みオブジェクトを取得する
	/// </summary>
	class StageLoader
	{
	public:

		static std::vector<std::unique_ptr<GameObject>> Load(const std::string& path);
	};
}
