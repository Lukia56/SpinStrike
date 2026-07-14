#pragma once

#include <cassert>
#include <string>

namespace Data
{
	/// <summary>
	/// 定義されていない型を使用した場合にコンパイルエラーにする
	/// </summary>
	template <typename T>
	T Convert(const std::string& str)
	{
		static_assert(sizeof(T) == 0, "Data // 定義されていない型に変換できません");

		return T{};
	}

	template <>
	int Convert<int>(const std::string& str)
	{
		return std::stoi(str);
	}

	template <>
	float Convert<float>(const std::string& str)
	{
		return std::stof(str);
	}

	template <>
	double Convert<double>(const std::string& str)
	{
		return std::stod(str);
	}

	template <>
	bool Convert<bool>(const std::string& str)
	{
		if (str == "TRUE" || str == "1") return true;
		if (str == "FALSE" || str == "0") return false;

		assert(false && "Data // 不適切な文字列のため、bool型への変換に失敗しました");
		return false;
	}

	/// <summary>
	/// 未定義のコンパイルエラー回避用に文字列をそのまま返す
	/// </summary>
	template <>
	std::string Convert<std::string>(const std::string& str)
	{
		return str;
	}
}
