#pragma once

#include "FromCsv.h"

namespace Data
{
	namespace Csv
	{
		template <typename T>
		inline std::vector<T> LoadCsvAs(const std::string& path)
		{
			Table table = LoadRawCsv(path);

			if (table.empty())
			{
				assert(false && "Data::Csv // データテーブルが空です");
				return {};
			}

			std::vector<Row> rows = ToRows(table);

			if (rows.empty())
			{
				assert(false && "Data::Csv // 行データへの変換に失敗しました");
				return {};
			}

			std::vector<T> result;
			result.reserve(rows.size());
			
			// 構造体に変換する
			for (const auto& row : rows)
			{
				result.emplace_back(FromCsv<T>::Binding(row));
			}

			return result;
		}
	}
}
