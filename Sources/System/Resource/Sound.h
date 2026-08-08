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

		Sound(const std::string& path) : ResourceBase(path) {}
		~Sound();

	protected:

		void Delete() override;

	private:

		bool Load() override;
	};
}
