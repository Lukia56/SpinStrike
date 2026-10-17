#pragma once

#include "../Data.h"
#include <fstream>

namespace Data
{
	namespace Json
	{
		template <typename T>
		inline void ExportJsonAs(const std::string& path, const T& data)
		{
			JsonObject json = data;

			std::ofstream ofs(path);

			ofs << std::setw(4) << json << std::endl;
		}
	}
}
