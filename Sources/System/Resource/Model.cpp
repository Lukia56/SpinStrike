#include "Model.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	Model::~Model()
	{
		Delete();
	}

	int Model::GetHandle() const
	{
		return MV1DuplicateModel(mHandle);
	}

	bool Model::Load()
	{
		mHandle = MV1LoadModel(mPath.c_str());

		return mHandle != -1;
	}

	void Model::Delete()
	{
		MV1DeleteModel(mHandle);
	}
}
