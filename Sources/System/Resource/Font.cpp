#include "Font.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	bool Font::Load(const std::string& path)
	{
		mHandle = LoadFontDataToHandle(path.c_str(), 1);

		return mHandle != -1;
	}
	void Font::Delete()
	{
		DeleteFontToHandle(mHandle);
	}
}
