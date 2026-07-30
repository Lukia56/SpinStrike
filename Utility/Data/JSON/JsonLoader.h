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

		/// <summary>
		/// ステージデータ読み込み用の特殊化
		/// 一番上の階層を無視して配列を取得するために使用
		/// </summary>
		template <>
		inline std::vector<StageObjectParam> LoadJsonAs(const std::string& path)
		{
			JsonObject json = LoadRawJson(path);

			if (json.empty()) { assert(false && "Data::Json // JSONデータが空です"); return {}; }
			if (!json.is_object()) { assert(false && "Data::Json // ステージデータはobject型である必要があります"); return {}; }
			if (!json.contains("objects")) { assert(false && "Data::Json // ステージデータにはobjectsキーが必要です"); return {}; }

			JsonObject objectsJson = json.at("objects");

			std::vector<StageObjectParam> result;

			// 配列でないなら要素1の配列として返す
			if (!objectsJson.is_array())
			{
				assert(false && "Data::Json // ステージデータのobjectsは配列にする必要があります");
				return result;
			}

			result.reserve(objectsJson.size());

			// 構造体に変換する
			for (const auto& obj : objectsJson)
			{
				result.emplace_back(FromJson<StageObjectParam>::Binding(obj));
			}

			return result;
		}
	}
}
