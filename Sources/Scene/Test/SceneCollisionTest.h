#pragma once

#include "../SceneBase.h"
#include "Utility/Vector.h"

namespace Collision
{
	class IShape3D;
}

class SceneCollisionTest : public SceneBase
{
public:

	SceneCollisionTest();
	~SceneCollisionTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

	void OnDebugDraw() override;

private:

	std::unique_ptr<Collision::IShape3D> mShapeA;
	std::unique_ptr<Collision::IShape3D> mShapeB;

	Vector3 mShapeAPos;
	Vector3 mShapeBPos;

	bool mIsControllCamera;

	bool mIsStartTransition;
};
