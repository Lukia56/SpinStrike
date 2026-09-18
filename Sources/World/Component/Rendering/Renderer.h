#pragma once

#include <memory>
#include "Utility/Vector.h"

class GameObject;
namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// グラフィックリソースの描画を行う基底
/// </summary>
class Renderer
{
public:

	Renderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource);
	virtual ~Renderer() = default;

	virtual void Draw() const = 0;

public:

	void SetOffsetPos(const Vector3& offsetPos) { mOffsetPos = offsetPos; }

protected:

	std::shared_ptr<Resource::ResourceBase> mResource;

	GameObject* mOwner;

	Vector3 mOffsetPos;
};
