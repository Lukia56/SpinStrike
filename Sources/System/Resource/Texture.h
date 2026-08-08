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

	protected:

		void Delete() override;

	private:

		bool Load() override;
	};
}
