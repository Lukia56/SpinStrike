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

		Texture() = default;
		~Texture() = default;

	private:

		bool Load(const std::string& path) override;

		void Delete() override;
	};
}
