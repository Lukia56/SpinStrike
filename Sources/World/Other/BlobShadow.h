#pragma once

#include "../GameObject.h"

namespace Collision
{
	struct Ray;
}
namespace Resource
{
	class ResourceBase;
}

class BlobShadow : public GameObject
{
public:

	BlobShadow(std::shared_ptr<Resource::ResourceBase> texture);
	~BlobShadow() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	/// <param name="ray">オフセットを加えるためコピー</param>
	/// <param name="offset"></param>
	/// <param name="centerPos">出力用に参照</param>
	bool RaycastOffset(Collision::Ray ray, const Vector3& offset, Vector3& centerPos);

private:

	std::shared_ptr<Resource::ResourceBase> mTexture;
};
