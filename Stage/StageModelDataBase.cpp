#include "StageModelDataBase.h"
#include <cassert>
#include "Utility/Data/Data.h"

namespace
{
	const char* const kDataPath = "Resource\\MasterData\\StageModelData.csv";

	constexpr size_t kObjectNameIndex = 0;
	constexpr size_t kFilePathIndex = 1;
}

Stage::StageModelDataBase::StageModelDataBase()
{
	Data::Csv::Table table = Data::Csv::LoadRawCsv(kDataPath);

	// オブジェクト名をキー、ファイルパスを値にして格納する
	for (size_t i = 1; i < table.size(); i++)
	{
		const std::vector<std::string>& row = table[i];
		mData.try_emplace(row[kObjectNameIndex], row[kFilePathIndex]);
	}
}

std::string Stage::StageModelDataBase::GetFilePath(const std::string& objectName)
{
	if (!mData.contains(objectName))
	{
		assert(false && "StageModelDataBase // 指定されたオブジェクト名が存在しないため、ファイルパスを取得できませんでした");
		return "";
	}

	return mData.at(objectName);
}
