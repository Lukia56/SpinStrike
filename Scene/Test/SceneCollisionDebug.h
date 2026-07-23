#pragma once

#include "../SceneBase.h"
#include "Utility/Vector.h"

namespace Collision
{
	class IShape3D;
}

class SceneCollisionDebug : public SceneBase
{
public:

	SceneCollisionDebug();
	~SceneCollisionDebug() = default;

	void Init() override;

	std::unique_ptr<SceneBase> Update() override;

	void DebugDraw() override;

private:

	std::unique_ptr<Collision::IShape3D> mShapeA;
	std::unique_ptr<Collision::IShape3D> mShapeB;

	Vector3 mShapeAPos;
	Vector3 mShapeBPos;

	bool mIsControllCamera;
};
