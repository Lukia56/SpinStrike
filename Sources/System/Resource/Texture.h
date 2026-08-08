#pragma once

#include "ResourceBase.h"

namespace Resource
{
	/// <summary>
	/// テクスチャを管理するクラス
	/// </summary>
	class Texture : public ResourceBase
	{
	public:

		Texture(const std::string& path) : ResourceBase(path) {}
		~Texture();

	private:

		bool Load() override;

		void Delete() override;
	};
}
