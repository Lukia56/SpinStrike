#pragma once

#include "Renderer.h"

class RectTransform;

/// <summary>
/// 矩形を使用してUI画像の描画を行う
/// </summary>
class UIImageRenderer : public Renderer
{
public:

	UIImageRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource, RectTransform* rectTransform);
	~UIImageRenderer() = default;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

public:

	/// <summary>
	/// スケーリングしたテクスチャのサイズを取得する
	/// </summary>
	Vector2 GetTexSize() const;

private:

	Vector2 mTexSize;

	RectTransform* mRectTransform;
};
