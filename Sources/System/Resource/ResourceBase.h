#pragma once

#include <string>

class ResourceManager;

namespace Resource
{
	/// <summary>
	/// リソース系クラスの基底
	/// </summary>
	class ResourceBase
	{
	public:

		ResourceBase();
		virtual ~ResourceBase() = default;

		virtual int GetHandle() const { return mHandle; }

	protected:

		int mHandle;

	private:

		friend ResourceManager;
	
		/// <summary>
		/// 読み込み処理がリソースごとに違うため純粋仮想化
		/// </summary>
		/// <returns>読み込みに成功したらtrue</returns>
		virtual bool Load(const std::string& path) = 0;

		/// <summary>
		/// 解放処理がリソースごとに違うため純粋仮想化
		/// </summary>
		virtual void Delete() = 0;
	};
}
