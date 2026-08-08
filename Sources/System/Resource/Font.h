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

	protected:
		
		void Delete() override;

	private:

		bool Load() override;
	};
}
