#include "Texture.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	bool Texture::Load(const std::string& path)
	{
		mHandle = LoadGraph(path.c_str());

		return mHandle != -1;
	}

	void Texture::Delete()
	{
		DeleteGraph(mHandle);
	}
}
