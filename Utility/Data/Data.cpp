#include "Data.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Data
{
	namespace Csv
	{
		Table LoadRawCsv(const std::string& path)
		{
			Table table;

			// ファイルの読み込み
			std::ifstream fIn(path);
			if (fIn.fail())
			{
				assert(false && "Data::Csv // CSVファイルの読み込みに失敗しました");
				return table;
			}
			
			// セルごとに分割してテーブルに格納する
			std::string line;
			while (std::getline(fIn, line))
			{
				// 行が空だったらスキップ
				if (line.empty())
				{
					assert(false && "Data::Csv // 空の行があります");
					continue;
				}

				table.emplace_back(Split(line));
			}

			return table;
		}

		std::vector<Row> ToRows(const Table& table, char ignoreColumnPrefix)
		{
			std::vector<Row> rows;

			if (table.empty())
			{
				assert(false && "Data::Csv // データテーブルが空です");
				return rows;
			}
			if (table.size() < 2)
			{
				assert(false && "Data::Csv // ヘッダのみでデータがありません");
				return rows;
			}
			
			// 最初の行をヘッダとして取得
			const std::vector<std::string>& header = table[0];

			// 2行目以降をデータとして取得
			for (int i = 1; i < table.size(); i++)
			{
				const std::vector<std::string>& line = table[i];

				// ヘッダにキーにしてデータを格納
				Row row;
				for (size_t j = 0; j < header.size(); j++)
				{
					if (j >= line.size())
					{
						assert(false && "Data::Csv // ヘッダに対応したデータがありません");
						break;
					}
					if (header[j].empty())
					{
						assert(false && "Data::Csv // ヘッダが空です");
						continue;
					}

					if (header[j][0] == ignoreColumnPrefix) continue;

					row[header[j]] = line[j];
				}

				rows.emplace_back(row);
			}

			return rows;
		}

		std::vector<std::string> Split(const std::string& rawString, char separate)
		{
			std::vector<std::string> separatedString;

			// 列ごとに文字列を分割する
			std::string buf = "";
			bool isQuates = false;

			for (size_t i = 0; i < rawString.length(); i++)
			{
				char checkChar = rawString[i];

				if (checkChar == '"')
				{
					isQuates = !isQuates;
					continue;
				}
				else
				// 現在の列の文字列を確定して、次の列の準備をする
				if (checkChar == separate && !isQuates)
				{
					separatedString.emplace_back(buf);
					buf.clear();
					continue;
				}
				
				buf += checkChar;
			}

			// 最後の列は区切り文字がないため別途追加
			separatedString.emplace_back(buf);

			return separatedString;
		}
	}
}
