#pragma once

#include "ResourceBase.h"

namespace Resource
{
	/// <summary>
	/// ƒ‚ƒfƒ‹‚ğŠÇ—‚·‚éƒNƒ‰ƒX
	/// </summary>
	class Model : public ResourceBase
	{
	public:

		Model(const std::string& path) : ResourceBase(path) {}
		~Model();

		int GetHandle() const override;

	private:

		bool Load() override;

		void Delete() override;
	};
}
