#pragma once

#include "Renderer.h"
#include "System/Resource/Model.h"

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

	int GetHandle() const { return mModelHandle; };

private:

	int mModelHandle;
};
