#pragma once

#include "UIObject.h"
#include <string>

class UIImageRenderer;

namespace UI
{
	/// <summary>
	/// UI‰æ‘œ‚ð•\Ž¦‚·‚é
	/// </summary>
	class Image : public UIObject
	{
	public:

		Image(const std::string& texturePath);
		~Image() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	private:

		std::unique_ptr<UIImageRenderer> mRenderer;
	};
}
