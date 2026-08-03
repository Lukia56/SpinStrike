#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <json.hpp>

namespace Data
{
	namespace Csv
	{
		using Table = std::vector<std::vector<std::string>>;
		using Row = std::unordered_map<std::string, std::string>;

		/// <summary>
		/// CSVファイルを読み込んで文字列の二次元配列に変換する
		/// </summary>
		Table LoadRawCsv(const std::string& path);

		/// <summary>
		/// ヘッダをキーにしたマップに変換する
		/// 特定の接頭辞が使われているヘッダは無視する
		/// </summary>
		/// <param name="table">無加工のデータテーブル</param>
		/// <param name="ignoreColumnPrefix">無視する行の接頭辞</param>
		std::vector<Row> ToRows(const Table& table, char ignoreColumnPrefix = '_');

		/// <summary>
		/// 文字列を分割する
		/// </summary>
		std::vector<std::string> Split(const std::string& rawString, char separate = ',');
	}

	namespace Json
	{
		using JsonObject = nlohmann::json;

		JsonObject LoadRawJson(const std::string& path);
	}
}
