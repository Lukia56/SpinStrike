#include "Model.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	int Model::GetHandle() const
	{
		return MV1DuplicateModel(mHandle);
	}

	bool Model::Load(const std::string& path)
	{
		mHandle = MV1LoadModel(path.c_str());

		return mHandle != -1;
	}

	void Model::Delete()
	{
		MV1DeleteModel(mHandle);
	}
}
