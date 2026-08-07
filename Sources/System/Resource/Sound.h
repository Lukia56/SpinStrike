#pragma once

#include "ResourceBase.h"

namespace Resource
{
	/// <summary>
	/// サウンドを管理するクラス
	/// </summary>
	class Sound : public ResourceBase
	{
	public:

		Sound() = default;
		~Sound() = default;

	private:

		bool Load(const std::string& path) override;

		void Delete() override;
	};
}
