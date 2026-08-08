#pragma once

#include "ResourceBase.h"

namespace Resource
{
	/// <summary>
	/// フォントを管理するクラス
	/// </summary>
	class Font : public ResourceBase
	{
	public:

		Font(const std::string& path) : ResourceBase(path) {}
		~Font();

	private:

		bool Load() override;

		void Delete() override;
	};
}
