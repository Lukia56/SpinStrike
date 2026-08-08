#include "Texture.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	Texture::~Texture()
	{
		Delete();
	}

	bool Texture::Load()
	{
		mHandle = LoadGraph(mPath.c_str());

		return mHandle != -1;
	}

	void Texture::Delete()
	{
		DeleteGraph(mHandle);
	}
}
