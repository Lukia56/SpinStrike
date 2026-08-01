#pragma once

#include <string>
#include <unordered_map>

namespace Stage
{
	/// <summary>
	/// ステージで使用するモデルのデータベース
	/// </summary>
	class StageModelDataBase
	{
	public:

		StageModelDataBase();

		/// <summary>
		/// オブジェクト名からファイルパスを取得する
		/// 取得に失敗した場合は空の文字列を返す
		/// </summary>
		std::string GetFilePath(const std::string& objectName);

	private:

		std::unordered_map<std::string, std::string> mData;
	};
}
