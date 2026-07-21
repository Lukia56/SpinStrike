#pragma once

#include <cassert>
#include <sstream>
#include "Utility/Vector.h"
#include "World/Components/CollisionTag.h"

namespace Data
{
	namespace Csv
	{
		/// <summary>
		/// 定義されていない型を使用した場合にコンパイルエラーにする
		/// </summary>
		template <typename T>
		inline T Convert(const std::string& str)
		{
			static_assert(sizeof(T) == 0, "Data::Csv // Cannot convert an undefined type");

			return T{};
		}

		template <>
		inline int Convert<int>(const std::string& str)
		{
			return std::stoi(str);
		}

		template <>
		inline float Convert<float>(const std::string& str)
		{
			return std::stof(str);
		}

		template <>
		inline double Convert<double>(const std::string& str)
		{
			return std::stod(str);
		}

		template <>
		inline bool Convert<bool>(const std::string& str)
		{
			if (str == "TRUE" || str == "1") return true;
			if (str == "FALSE" || str == "0") return false;

			assert(false && "Data::Csv // 不適切な文字列のため、bool型への変換に失敗しました");
			return false;
		}

		/// <summary>
		/// 未定義のコンパイルエラー回避用に文字列をそのまま返す
		/// </summary>
		template <>
		inline std::string Convert<std::string>(const std::string& str)
		{
			return str;
		}

		template <>
		inline Vector2 Convert<Vector2>(const std::string& str)
		{
			Vector2 vec;

			std::stringstream ss(str);
			char separateChar = ',';

			ss >> vec.x >> separateChar >> vec.y;

			return vec;
		}

		template <>
		inline Vector3 Convert<Vector3>(const std::string& str)
		{
			Vector3 vec;

			std::stringstream ss(str);
			char separateChar = ',';

			ss >> vec.x >> separateChar >> vec.y >> separateChar >> vec.z;

			return vec;
		}

		template <>
		inline Collision::Tag Convert<Collision::Tag>(const std::string& str)
		{
			return static_cast<Collision::Tag>(std::stoi(str));
		}
	}
}
