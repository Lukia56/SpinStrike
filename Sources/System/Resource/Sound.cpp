#include "Sound.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	Sound::~Sound()
	{
		Delete();
	}

	bool Sound::Load()
	{
		mHandle = LoadSoundMem(mPath.c_str());

		return mHandle != -1;
	}

	void Sound::Delete()
	{
		DeleteSoundMem(mHandle);
	}
}
