#pragma once

#include "ResourceBase.h"

namespace Resource
{
	/// <summary>
	/// エフェクトを管理するクラス
	/// </summary>
	class Effect : public ResourceBase
	{
	public:

		Effect() = default;
		~Effect() = default;

	private:

		bool Load(const std::string& path) override;

		void Delete() override;
	};
}
