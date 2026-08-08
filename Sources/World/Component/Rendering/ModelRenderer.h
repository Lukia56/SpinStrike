#pragma once

#include "Renderer.h"
#include "System/Resource/Model.h"

class ModelInstance;

/// <summary>
/// モデルの描画を行う
/// </summary>
class ModelRenderer : public Renderer<Resource::Model>
{
public:

	ModelRenderer(GameObject* owner);
	~ModelRenderer();

	void Load(const std::string& filePath) override;

	/// <summary>
	/// モデルをゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() override;

	/// <summary>
	/// モデルの移動量を無効化する
	/// </summary>
	void DisableMovement(const std::string& rootName);

public:

	int GetHandle();

private:

	std::unique_ptr<ModelInstance> mModelInstance;
};
