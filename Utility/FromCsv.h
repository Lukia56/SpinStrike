#pragma once

#include "Data.h"
#include "CsvConvert.h"

struct Param
{
	int count = -1;
	int hp = -1;
	bool flag = false;
	std::string text = "";
	Vector3 vec;
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
				param.count = Convert<int>(row.at("header1"));
				param.hp = Convert<int>(row.at("header2"));
				param.flag = Convert<bool>(row.at("header3"));
				param.text = Convert<std::string>(row.at("header4"));
				param.vec = Convert<Vector3>(row.at("header5"));
				return param;
			}
		};
	}
}
