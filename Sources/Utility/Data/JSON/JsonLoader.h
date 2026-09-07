#pragma once

#include "FromJson.h"

namespace Data
{
	namespace Json
	{
		template <typename T>
		inline std::vector<T> LoadJsonAs(const std::string& path)
		{
			JsonObject json = LoadRawJson(path);

			if (json.empty())
			{
				assert(false && "Data::Json // JSONデータが空です");
				return {};
			}

			std::vector<T> result;

			// 配列でないなら要素1の配列として返す
			if (!json.is_array())
			{
				result.emplace_back(FromJson<T>::Binding(json));
				return result;
			}

			result.reserve(json.size());

			// 構造体に変換する
			for (const auto& obj : json)
			{
				result.emplace_back(FromJson<T>::Binding(obj));
			}

			return result;
		}
	}
}
