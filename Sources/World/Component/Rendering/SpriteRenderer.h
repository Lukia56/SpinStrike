#pragma once

#include "Renderer.h"
#include "System/Resource/Texture.h"
#include "Utility/Vector.h"

namespace Resource
{
	class Texture;
}

/// <summary>
/// 画像の描画を行う
/// </summary>
class SpriteRenderer : public Renderer<Resource::Texture>
{
public:

	SpriteRenderer(GameObject* owner);
	~SpriteRenderer() = default;

	/// <summary>
	/// クラスのテンプレート引数のリソースの読み込みを行う
	/// 読み込みに成功したら画像の半径も取得する
	/// </summary>
	void Load(const std::string& filePath) override;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

private:

	Vector2 mTexHalfSize;
};

