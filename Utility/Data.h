#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace Data
{
	namespace Csv
	{
		using Table = std::vector<std::vector<std::string>>;
		using Row = std::unordered_map<std::string, std::string>;

		/// <summary>
		/// CSVファイルを読み込んで文字列の二次元配列に変換する
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		Table LoadRawCsv(const std::string& path);

		/// <summary>
		/// ヘッダをキーにしたマップに変換する
		/// </summary>
		std::vector<Row> ToRows(const Table& table);

		/// <summary>
		/// 文字列を分割する
		/// </summary>
		std::vector<std::string> Split(const std::string& rawString, char separate = ',');
	}
}
