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

		Font() = default;
		~Font() = default;

	private:

		bool Load(const std::string& path) override;

		void Delete() override;
	};
}
