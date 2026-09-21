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

	ModelRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource, std::shared_ptr<Resource::ResourceBase> animation = nullptr);
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

	int GetModelHandle() const;

	int GetAnimModelHandle() const;

private:

	std::unique_ptr<ModelInstance> mModelInstance;

	/// <summary>
	/// アニメーション参照用でモデルを複製する必要がないため直で管理
	/// </summary>
	std::shared_ptr<Resource::ResourceBase> mAnimModel;
};
