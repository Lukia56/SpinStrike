#pragma once

#include "../Data.h"
#include "JsonConvert.h"
#include "Param/Param.h"

namespace Data
{
	namespace Json
	{
		template <typename T>
		struct FromJson
		{
			static T Binding(const JsonObject& json)
			{
				static_assert(sizeof(T) == 0, "Data::Json::FromJson // Cannot binding an undefined type");

				return T{};
			}
		};

		/// <summary>
		/// 安全な値の取得処理
		/// </summary>
		template <typename T>
		T Get(const JsonObject& json, const std::string& key)
		{
			try
			{
				T value = Convert<T>(json.at(key));

				return value;
			}
			catch (JsonObject::out_of_range)
			{
				assert(false && "Data::Json::Get // 存在しないパラメータ名のため値の取得に失敗しました");

				return T{};
			}
		}
	}
}
