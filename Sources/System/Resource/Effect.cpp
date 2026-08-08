#include "Effect.h"
#include <string>
#include <EffekseerForDXLib.h>

namespace Resource
{
	Effect::~Effect()
	{
		Delete();
	}

	bool Effect::Load()
	{
		mHandle = LoadEffekseerEffect(mPath.c_str());

		return mHandle != -1;
	}

	void Effect::Delete()
	{
		DeleteEffekseerEffect(mHandle);
	}
}
