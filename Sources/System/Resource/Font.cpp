#include "Font.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	Font::~Font()
	{
		Delete();
	}

	bool Font::Load()
	{
		mHandle = LoadFontDataToHandle(mPath.c_str(), 1);

		return mHandle != -1;
	}

	void Font::Delete()
	{
		DeleteFontToHandle(mHandle);
	}
}
