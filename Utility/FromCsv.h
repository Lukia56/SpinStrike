#pragma once

#include "Data.h"
#include "CsvConvert.h"

struct Param
{
	int count = -1;
	int hp = -1;
	bool flag = false;
	Vector3 vec;
	std::string text = "";
};

namespace Data
{
	namespace Csv
	{
		template <typename T>
		struct FromCsv
		{
			static T Binding(const Row& row)
			{
				static_assert(sizeof(T) == 0, "Data::Csv::FromCsv // ’è‹`‚³‚ê‚Ä‚¢‚È‚¢Œ^‚ÉŠ„‚è“–‚Ä‚Å‚«‚Ü‚¹‚ñ");

				return T{};
			}
		};

		template <>
		struct FromCsv<Param>
		{
			static Param Binding(const Row& row)
			{
				Param param;
				param.count = Convert<int>(row.at("count"));
				param.hp = Convert<int>(row.at("hp"));
				param.flag = Convert<bool>(row.at("flag"));
				param.vec = Convert<Vector3>(row.at("vec"));
				param.text = Convert<std::string>(row.at("text"));
				return param;
			}
		};
	}
}
