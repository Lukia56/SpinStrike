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

		ResourceBase(const std::string& path);
		virtual ~ResourceBase();

		int GetHandle() const { return mHandle; }

	protected:

		/// <summary>
		/// 解放処理がリソースごとに違うため純粋仮想化
		/// </summary>
		virtual void Delete() = 0;

	private:

		// ResourceManager以外にはアクセスできないようにfriend指定
		friend ResourceManager;
	
		/// <summary>
		/// 読み込み処理がリソースごとに違うため純粋仮想化
		/// </summary>
		/// <returns>読み込みに成功したらtrue</returns>
		virtual bool Load() = 0;

	protected:

		int mHandle;

		std::string mPath;
	};
}
