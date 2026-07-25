#include "Collision3D.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "Utility/Geometry.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	constexpr int kDimensionNum = 3;

	/// <summary>
	/// AABBと球の衝突判定
	/// </summary>
	Collision::Result Check(const Collision::AABB3D* aabb, const Collision::Sphere3D* sphere)
	{
		Collision::Result result;

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

	Collision::Result CheckCapsuleSphere(const Collision::Capsule3D* capsule, const Collision::Sphere3D* sphere)
	{
		Collision::Result result;

		Vector3 spherePos = sphere->GetPosition();

		Vector3 minDistance = Geometry::CalculatePointSegmentDistance(spherePos, capsule->GetStartPos(), capsule->GetEndPos());

		float radiusSum = capsule->GetRadius() + sphere->GetRadius();

		// 衝突しているかチェック
		if (minDistance.GetSqLength() > Math::Sqr(radiusSum)) return result;
		
		result.isHit = true;

		// めり込みの法線を計算
		result.normal = minDistance.GetNormalize();
		if (result.normal == Vector3::Zero) result.normal = Vector3::XAxis;

		// めり込み具合を計算
		result.penetration = radiusSum - minDistance.GetLength();

		return result;
	}
}

namespace Collision
{
	// 球

	Sphere3D::Sphere3D() :
		mCenterPos(Vector3::Zero),
		mOffsetPos(Vector3::Zero),
		mRadius(0.0f)
	{
	}

	Sphere3D::Sphere3D(float radius, const Vector3& offset) :
		mCenterPos(Vector3::Zero),
		mOffsetPos(offset),
		mRadius(radius)
	{
	}

	void Sphere3D::DebugDraw(const Color& color) const
	{
		DrawSphere3D(GetPosition().GetAsDxLibVector(), mRadius, 10, color.GetAsHexRGB(), color.GetAsHexRGB(), false);
	}

	Collision::Result Sphere3D::Check(const Sphere3D* other) const
	{
		Collision::Result result;

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

	Collision::Result Sphere3D::Check(const AABB3D* other) const
	{
		Collision::Result result = ::Check(other, this);
		result.normal *= -1;
		return result;
	}

	Collision::Result Sphere3D::Check(const Capsule3D* other) const
	{
		Collision::Result result = ::CheckCapsuleSphere(other, this);
		result.normal *= -1;
		return result;
	}

	// AABB

	AABB3D::AABB3D(const Vector3& size, const Vector3& offset) :
		mCenterPos(Vector3::Zero),
		mOffsetPos(offset),
		mHalfSize(size * 0.5f)
	{
	}

	void AABB3D::DebugDraw(const Color& color) const
	{
		Vector3 minPos = this->GetPosition() - this->GetHalfSize();
		Vector3 maxPos = this->GetPosition() + this->GetHalfSize();

		DrawCube3D(minPos.GetAsDxLibVector(), maxPos.GetAsDxLibVector(), color.GetAsHexRGB(), color.GetAsHexRGB(), false);
	}

	Collision::Result AABB3D::Check(const Sphere3D* other) const
	{
		return ::Check(this, other);
	}

	Collision::Result AABB3D::Check(const AABB3D* other) const
	{
		Collision::Result result;

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

	Collision::Result AABB3D::Check(const Capsule3D* other) const
	{
		return Collision::Result();
	}

	// カプセル

	Capsule3D::Capsule3D(const Vector3& start, const Vector3& end, float radius, const Vector3& offset) :
		mStartPos(start),
		mEndPos(end),
		mRadius(radius),
		mOffsetPos(offset)
	{
	}

	void Capsule3D::DebugDraw(const Color& color) const
	{
		DrawCapsule3D(mStartPos.GetAsDxLibVector(), mEndPos.GetAsDxLibVector(), mRadius, 10, color.GetAsHexRGB(), color.GetAsHexRGB(), false);

		DrawLine3D(mStartPos.GetAsDxLibVector(), mEndPos.GetAsDxLibVector(), Color::cyan.GetAsHexRGB());
	}

	void Capsule3D::SetPosition(const Vector3& pos)
	{
		Vector3 center = GetPosition();

		Vector3 move = pos - center + mOffsetPos * 2.0f;

		mStartPos += move;
		mEndPos += move;
	}

	Vector3 Capsule3D::GetPosition() const
	{
		return (mStartPos + mEndPos) * 0.5f + mOffsetPos;
	}

	Collision::Result Capsule3D::Check(const Sphere3D* other) const
	{
		return ::CheckCapsuleSphere(this, other);
	}

	Collision::Result Capsule3D::Check(const AABB3D* other) const
	{
		return Collision::Result();
	}

	Collision::Result Capsule3D::Check(const Capsule3D* other) const
	{
		return Collision::Result();
	}
}
