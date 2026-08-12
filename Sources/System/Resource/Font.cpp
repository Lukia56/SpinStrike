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
		mHandle = LoadFontDataToHandle(mPath.c_str());

		return mHandle != -1;
	}

	void Font::Delete()
	{
		DeleteFontToHandle(mHandle);
	}
}
