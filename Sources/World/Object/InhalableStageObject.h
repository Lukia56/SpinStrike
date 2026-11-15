#pragma once

#include "StageObject.h"

class Collider3D;

class InhalableStageObject : public StageObject
{
public:

	InhalableStageObject(const StageObjectParam& param, std::shared_ptr<Resource::ResourceBase> model);
	~InhalableStageObject() = default;

	void Init() override;
	void Update() override;
	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;
};
