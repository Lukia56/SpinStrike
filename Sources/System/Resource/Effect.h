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

		Effect(const std::string& path) : ResourceBase(path) {}
		~Effect();

	private:

		bool Load() override;

		void Delete() override;
	};
}
