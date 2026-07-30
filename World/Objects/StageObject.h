#pragma once

#include "../GameObject.h"
#include "Param/Param.h"

class ModelRenderer;
class Collider3D;

/// <summary>
/// ステージ上の静的なオブジェクト
/// </summary>
class StageObject : public GameObject
{
public:

	StageObject();
	StageObject(const StageObjectParam& param);
	~StageObject() = default;

	void Init() override;
	void Update() override;
	void Draw() override;
	void DebugDraw() override;

private:

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<Collider3D> mCollider;
};

