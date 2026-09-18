#pragma once

#include "Renderer.h"
#include <string>

class ModelInstance;

/// <summary>
/// モデルの描画を行う
/// </summary>
class ModelRenderer : public Renderer
{
public:

	ModelRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource);
	~ModelRenderer();

	/// <summary>
	/// モデルをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// モデルの移動量を無効化する
	/// </summary>
	void DisableMovement(const std::string& rootName);

public:

	int GetHandle() const;

private:

	std::unique_ptr<ModelInstance> mModelInstance;
};
