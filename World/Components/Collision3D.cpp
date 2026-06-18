#include "Collision3D.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	constexpr int kDimensionNum = 3;

	/// <summary>
	/// AABBと球の衝突判定
	/// </summary>
	Collision3D::Result Check(const Collision3D::AABB3D* aabb, const Collision3D::Sphere3D* sphere)
	{
		Collision3D::Result result;

		// 座標をキャッシュ
		Vector3 aabbMinPos = aabb->GetPosition() - aabb->GetHalfSize();
		Vector3 aabbMaxPos = aabb->GetPosition() + aabb->GetHalfSize();
		Vector3 spherePos = sphere->GetPosition();

		float sphereRadius = sphere->GetRadius();

		// 衝突していないか計算
		float sqLength = 0.0f;
		for (int i = 0; i < kDimensionNum; i++)
		{
			if (spherePos[i] < aabbMinPos[i])
			{
				sqLength += Math::Sqr(spherePos[i] - aabbMinPos[i]);
			}
			else if (spherePos[i] > aabbMaxPos[i])
			{
				sqLength += Math::Sqr(spherePos[i] - aabbMaxPos[i]);
			}
		}
		if (sqLength > Math::Sqr(sphereRadius)) return result;

		result.isHit = true;

		// めり込み具合を計算
		Vector3 overlaps;
		overlaps.x = Math::Min(aabbMaxPos.x, spherePos.x + sphereRadius) - Math::Max(aabbMinPos.x, spherePos.x - sphereRadius);
		overlaps.y = Math::Min(aabbMaxPos.y, spherePos.y + sphereRadius) - Math::Max(aabbMinPos.y, spherePos.y - sphereRadius);
		overlaps.z = Math::Min(aabbMaxPos.z, spherePos.z + sphereRadius) - Math::Max(aabbMinPos.z, spherePos.z - sphereRadius);

		// めり込み量が一番少ない成分をめり込み具合にする
		float minOverlaps = overlaps.x;
		result.normal = Vector3::XAxis;
		if (minOverlaps > overlaps.y)
		{
			minOverlaps = overlaps.y;
			result.normal = Vector3::YAxis;
		}
		if (minOverlaps > overlaps.z)
		{
			minOverlaps = overlaps.z;
			result.normal = Vector3::ZAxis;
		}
		result.penetration = minOverlaps;

		// 法線の符号を計算
		Vector3 vect = aabb->GetPosition() - spherePos;
		if (result.normal == Vector3::XAxis)
		{
			result.normal *= (vect.x <= 0.0f ? 1.0f : -1.0f);
		}
		else if (result.normal == Vector3::YAxis)
		{
			result.normal *= (vect.y <= 0.0f ? 1.0f : -1.0f);
		}
		else if (result.normal == Vector3::ZAxis)
		{
			result.normal *= (vect.z <= 0.0f ? 1.0f : -1.0f);
		}

		return result;
	}
}

namespace Collision3D
{
	// 球

	void Sphere3D::DebugDraw() const
	{
		DrawSphere3D(mCenterPos.GetAsDxLibVector(), mRadius, 10, Color::white.GetAsHexRGB(), Color::white.GetAsHexRGB(), false);
	}

	Collision3D::Result Sphere3D::Check(const Sphere3D* other) const
	{
		Collision3D::Result result;

		// 距離を計算
		Vector3 dist = this->GetPosition() - other->GetPosition();
		float sqDistLen = dist.GetSqLength();
		// 半径の和を計算
		float radiusSum = this->GetRadius() + other->GetRadius();

		// 衝突していないか計算
		if (sqDistLen > Math::Sqr(radiusSum)) return result;

		result.isHit = true;

		// めり込みの法線を計算
		result.normal = dist.GetNormalize();
		// 完全に同じ位置だったら法線の向きを変える
		if (result.normal == Vector3::Zero) result.normal = Vector3::XAxis;

		// めり込み具合を計算
		result.penetration = radiusSum - dist.GetLength();

		return result;
	}

	Collision3D::Result Sphere3D::Check(const AABB3D* other) const
	{
		Collision3D::Result result = ::Check(other, this);
		result.normal *= -1;
		return result;
	}

	Collision3D::Result Sphere3D::Check(const Capsule3D* other) const
	{
		return Collision3D::Result();
	}

	// AABB

	void AABB3D::DebugDraw() const
	{
		Vector3 minPos = this->GetPosition() - this->GetHalfSize();
		Vector3 maxPos = this->GetPosition() + this->GetHalfSize();

		DrawCube3D(minPos.GetAsDxLibVector(), maxPos.GetAsDxLibVector(), Color::white.GetAsHexRGB(), Color::white.GetAsHexRGB(), false);
	}

	Collision3D::Result AABB3D::Check(const Sphere3D* other) const
	{
		return ::Check(this, other);
	}

	Collision3D::Result AABB3D::Check(const AABB3D* other) const
	{
		Collision3D::Result result;

		// 角の座標をキャッシュ
		Vector3 myMinPos = this->GetPosition() - this->GetHalfSize();
		Vector3 myMaxPos = this->GetPosition() + this->GetHalfSize();
		Vector3 otherMinPos = other->GetPosition() - other->GetHalfSize();
		Vector3 otherMaxPos = other->GetPosition() + other->GetHalfSize();

		// 衝突していないか計算
		if (myMinPos.x > otherMaxPos.x) return result;
		if (myMaxPos.x < otherMinPos.x) return result;

		if (myMinPos.y > otherMaxPos.y) return result;
		if (myMaxPos.y < otherMinPos.y) return result;

		if (myMinPos.z > otherMaxPos.z) return result;
		if (myMaxPos.z < otherMinPos.z) return result;

		result.isHit = true;

		// めり込み具合を計算
		Vector3 overlaps;
		overlaps.x = Math::Min(myMaxPos.x, otherMaxPos.x) - Math::Max(myMinPos.x, otherMinPos.x);
		overlaps.y = Math::Min(myMaxPos.y, otherMaxPos.y) - Math::Max(myMinPos.y, otherMinPos.y);
		overlaps.z = Math::Min(myMaxPos.z, otherMaxPos.z) - Math::Max(myMinPos.z, otherMinPos.z);

		// めり込み量が一番少ない成分をめり込み具合にする
		float minOverlaps = overlaps.x;
		result.normal = Vector3::XAxis;
		if (minOverlaps > overlaps.y)
		{
			minOverlaps = overlaps.y;
			result.normal = Vector3::YAxis;
		}
		if (minOverlaps > overlaps.z)
		{
			minOverlaps = overlaps.z;
			result.normal = Vector3::ZAxis;
		}
		result.penetration = minOverlaps;

		// 法線の符号を計算
		Vector3 vect = this->GetPosition() - other->GetPosition();
		if (result.normal == Vector3::XAxis)
		{
			result.normal *= (vect.x <= 0.0f ? 1.0f : -1.0f);
		}
		else if (result.normal == Vector3::YAxis)
		{
			result.normal *= (vect.y <= 0.0f ? 1.0f : -1.0f);
		}
		else if (result.normal == Vector3::ZAxis)
		{
			result.normal *= (vect.z <= 0.0f ? 1.0f : -1.0f);
		}

		return result;
	}

	Collision3D::Result AABB3D::Check(const Capsule3D* other) const
	{
		return Collision3D::Result();
	}

	void Capsule3D::DebugDraw() const
	{
	}

	Collision3D::Result Capsule3D::Check(const Sphere3D* other) const
	{
		return Collision3D::Result();
	}

	Collision3D::Result Capsule3D::Check(const AABB3D* other) const
	{
		return Collision3D::Result();
	}

	Collision3D::Result Capsule3D::Check(const Capsule3D* other) const
	{
		return Collision3D::Result();
	}
}
