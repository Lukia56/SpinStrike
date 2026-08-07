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

		Model() = default;
		~Model() = default;

		int GetHandle() const override;

	private:

		bool Load(const std::string& path) override;

		void Delete() override;
	};
}
