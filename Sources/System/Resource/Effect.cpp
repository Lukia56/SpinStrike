#include "Effect.h"
#include <string>
#include <EffekseerForDXLib.h>

namespace Resource
{
	bool Effect::Load(const std::string& path)
	{
		mHandle = LoadEffekseerEffect(path.c_str());

		return mHandle != -1;
	}

	void Effect::Delete()
	{
		DeleteEffekseerEffect(mHandle);
	}
}
