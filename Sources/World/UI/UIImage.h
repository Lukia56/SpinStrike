#pragma once

#include "UIObject.h"
#include <string>

class UIImageRenderer;

namespace UI
{
	/// <summary>
	/// UI画像を表示する
	/// 矩形はテクスチャのサイズで初期化する
	/// </summary>
	class Image : public UIObject
	{
	public:

		Image(const std::string& texturePath);
		~Image() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	public:

		/// <summary>
		/// 矩形のサイズをテクスチャのサイズに変更する
		/// スケールを変更した際や、矩形サイズ変更後に元に戻したいときに使用する
		/// </summary>
		void SetRectSizeToTexSize();

	private:

		std::unique_ptr<UIImageRenderer> mRenderer;
	};
}
