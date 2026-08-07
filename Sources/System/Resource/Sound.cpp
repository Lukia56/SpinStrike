#include "Sound.h"
#include <string>
#include <DxLib.h>

namespace Resource
{
	bool Sound::Load(const std::string& path)
	{
		mHandle = LoadSoundMem(path.c_str());

		return mHandle != -1;
	}

	void Sound::Delete()
	{
		DeleteSoundMem(mHandle);
	}
}
