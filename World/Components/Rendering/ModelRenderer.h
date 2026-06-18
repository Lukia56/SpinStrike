#pragma once

#include "Renderer.h"

/// <summary>
/// モデルの描画を行う
/// </summary>
class ModelRenderer : public Renderer<Model>
{
public:

	ModelRenderer(GameObject* owner);
	~ModelRenderer() = default;

	void Load(const std::string& filePath) override;

	/// <summary>
	/// モデルをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() override;

private:

	int mModelHandle;
};
