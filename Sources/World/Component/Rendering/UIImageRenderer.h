#pragma once

#include "Renderer.h"
#include "System/Resource/Texture.h"
#include "Utility/Vector.h"

class RectTransform;
namespace Resource
{
	class Texture;
}

/// <summary>
/// 矩形を使用してUI画像の描画を行う
/// </summary>
class UIImageRenderer : public Renderer<Resource::Texture>
{
public:

	UIImageRenderer(GameObject* owner, RectTransform* rectTransform);
	~UIImageRenderer() = default;

	/// <summary>
	/// クラスのテンプレート引数のリソースの読み込みを行う
	/// 読み込みに成功したら画像のサイズも取得する
	/// </summary>
	void Load(const std::string& filePath) override;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

public:

	const Vector2& GetTexSize() const { return mTexSize; }

private:

	Vector2 mTexSize;

	RectTransform* mRectTransform;
};
