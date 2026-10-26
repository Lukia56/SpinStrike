#include "BlobShadow.h"
#include <DxLib.h>
#include "Collision/CollisionManager.h"
#include "Collision/Ray.h"
#include "System/Resource/ResourceBase.h"
#include "../Component/Collider3D.h"

namespace
{
	constexpr Vector3 kRayDirection{ 0.0f, -1.0f, 0.0f };

	constexpr float kShadowRadius = 50.0f;
}

BlobShadow::BlobShadow(std::shared_ptr<Resource::ResourceBase> texture) :
	mTexture(texture)
{
}

void BlobShadow::Init()
{
}

void BlobShadow::Update()
{
}

void BlobShadow::Draw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	Collision::Ray ray{ .position = pos, .direction = kRayDirection };

	bool result = false;
	Vector3 centerPos;

	// 8方向+中心でレイキャスト
	if (RaycastOffset(ray, Vector3(kShadowRadius, 0.0f, 0.0f), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(-kShadowRadius, 0.0f, 0.0f), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(0.0f, 0.0f, kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(0.0f, 0.0f, -kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(kShadowRadius, 0.0f, kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(-kShadowRadius, 0.0f, kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(kShadowRadius, 0.0f, -kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3(-kShadowRadius, 0.0f, -kShadowRadius), centerPos)) result = true;
	if (RaycastOffset(ray, Vector3::Zero, centerPos)) result = true;

	if (!result) return;

	VERTEX3D vertices[4];

	// 共通する値を設定
	// 埋もれてしまうため少しだけ上に上げる
	vertices[0].pos = (centerPos + Vector3::YAxis).GetAsDxLibVector();
	vertices[0].norm = Vector3::YAxis.GetAsDxLibVector();
	vertices[0].dif = GetColorU8(255, 255, 255, 127);
	vertices[0].spc = GetColorU8(255, 255, 255, 127);
	vertices[0].su = 0.0f;
	vertices[0].sv = 0.0f;
	// 共有
	vertices[1] = vertices[0];
	vertices[2] = vertices[0];
	vertices[3] = vertices[0];

	// 個別に座標設定
	vertices[0].pos.x -= kShadowRadius;
	vertices[0].pos.z += kShadowRadius;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	vertices[1].pos.x += kShadowRadius;
	vertices[1].pos.z += kShadowRadius;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;

	vertices[2].pos.x -= kShadowRadius;
	vertices[2].pos.z -= kShadowRadius;
	vertices[2].u = 0.0f;
	vertices[2].v = 1.0f;

	vertices[3].pos.x += kShadowRadius;
	vertices[3].pos.z -= kShadowRadius;
	vertices[3].u = 1.0f;
	vertices[3].v = 1.0f;

	WORD indices[6] = { 0, 1, 2, 3, 2, 1 };

	SetUseLighting(false);
	DrawPolygonIndexed3D(vertices, 4, indices, 2, mTexture->GetHandle(), true);
	SetUseLighting(true);
}

bool BlobShadow::RaycastOffset(Collision::Ray ray, const Vector3& offset, Vector3& centerPos)
{
	ray.position += offset;

	// 地面にレイキャスト
	std::vector<Collision::RaycastResult> results = CollisionManager::GetInstance().Raycast(ray,
		[](Collider3D* collider) { return collider->GetOwner()->GetTag() == GameObject::Tag::Terrain; });

	if (results.empty()) return false;

	centerPos = results[0].collidePos - offset;

	return true;
}
