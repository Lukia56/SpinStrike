#include "StageModelDataBase.h"
#include <cassert>
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kDataPath = "Resources\\MasterData\\StageModelData.csv";
}

Stage::StageModelDataBase::StageModelDataBase()
{
	auto dataList = Data::Csv::LoadCsvAs<StageModelData>(kDataPath);

	for (const auto& data : dataList)
	{
		mData.try_emplace(data.objectName, data.filePath);
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
