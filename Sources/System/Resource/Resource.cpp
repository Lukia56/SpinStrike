#include "Resource.h"
#include <DxLib.h>
#include "../ResourceManager.h"

bool Texture::Load(const std::string& path)
{
	mHandle = LoadGraph(path.c_str());

	return mHandle != -1;
}
void Texture::Delete()
{
	DeleteGraph(mHandle);
}

int Model::GetHandle() const
{
	return MV1DuplicateModel(mHandle);
}
bool Model::Load(const std::string& path)
{
	mHandle = MV1LoadModel(path.c_str());

	return mHandle != -1;
}
void Model::Delete()
{
	MV1DeleteModel(mHandle);
}

bool Sound::Load(const std::string& path)
{
	mHandle = LoadSoundMem(path.c_str());

	return mHandle != -1;
}
void Sound::Delete()
{
	DeleteSoundMem(mHandle);
}

bool Font::Load(const std::string& path)
{
	mHandle = LoadFontDataToHandle(path.c_str(), 1);

	return mHandle != -1;
}
void Font::Delete()
{
	DeleteFontToHandle(mHandle);
}
