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
	/// 一番めり込んでいない軸のめり込み具合を計算する
	/// </summary>
	void CalculateBoxPenetrateVector(Collision::Result& result, const Vector3& minPosA, const Vector3& maxPosA, const Vector3& minPosB, const Vector3& maxPosB)
	{
		// めり込み具合を計算
		Vector3 overlaps;
		overlaps.x = Math::Min(maxPosA.x, maxPosB.x) - Math::Max(minPosA.x, minPosB.x);
		overlaps.y = Math::Min(maxPosA.y, maxPosB.y) - Math::Max(minPosA.y, minPosB.y);
		overlaps.z = Math::Min(maxPosA.z, maxPosB.z) - Math::Max(minPosA.z, minPosB.z);

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
		Vector3 centerA = (maxPosA + minPosA) * 0.5f;
		Vector3 centerB = (maxPosB + minPosB) * 0.5f;
		Vector3 vect = centerA - centerB;
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
	}

	Collision::Result CheckAABBSphere(const Collision::AABB3D* aabb, const Collision::Sphere3D* sphere)
	{
		Collision::Result result;

		// 座標をキャッシュ
		Vector3 aabbMinPos = aabb->GetWorldPos() - aabb->GetHalfSize();
		Vector3 aabbMaxPos = aabb->GetWorldPos() + aabb->GetHalfSize();
		Vector3 spherePos = sphere->GetWorldPos();

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

		// 球の最小座標と最大座標をキャッシュ
		Vector3 sphereRadiusVec = Vector3(sphereRadius, sphereRadius, sphereRadius);
		Vector3 sphereMinPos = spherePos - sphereRadiusVec;
		Vector3 sphereMaxPos = spherePos + sphereRadiusVec;

		// めり込み具合を計算
		CalculateBoxPenetrateVector(result, aabbMinPos, aabbMaxPos, sphereMinPos, sphereMaxPos);

		return result;
	}

	Collision::Result CheckCapsuleSphere(const Collision::Capsule3D* capsule, const Collision::Sphere3D* sphere)
	{
		Collision::Result result;

		Vector3 spherePos = sphere->GetWorldPos();

		Vector3 minDistance = Geometry::CalculatePointSegmentDistance(spherePos, capsule->GetStartPos(), capsule->GetEndPos());

		float radiusSum = capsule->GetRadius() + sphere->GetRadius();

		// 衝突しているかチェック
		if (minDistance.GetSqLength() > Math::Sqr(radiusSum)) return result;
		
		result.isHit = true;

		// めり込みの法線を計算
		float distanceLength = minDistance.GetLength();
		if (Math::IsNearZero(distanceLength))
		{
			result.normal = Vector3::XAxis;
		}
		else
		{
			result.normal = minDistance / distanceLength;
		}

		// めり込み具合を計算
		result.penetration = radiusSum - distanceLength;

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
		DrawSphere3D(GetWorldPos().GetAsDxLibVector(), mRadius, 10, color.GetAsHexRGB(), color.GetAsHexRGB(), false);
	}

	Collision::Result Sphere3D::Check(const Sphere3D* other) const
	{
		Collision::Result result;

		Vector3 distance = this->GetWorldPos() - other->GetWorldPos();
		float distanceSqLength = distance.GetSqLength();
		
		float radiusSum = this->GetRadius() + other->GetRadius();

		// 衝突しているかチェック
		if (distanceSqLength > Math::Sqr(radiusSum)) return result;

		result.isHit = true;

		// めり込みの法線を計算
		float distanceLength = distance.GetLength();
		if (Math::IsNearZero(distanceLength))
		{
			result.normal = Vector3::XAxis;
		}
		else
		{
			result.normal = distance / distanceLength;
		}

		// めり込み具合を計算
		result.penetration = radiusSum - distanceLength;

		return result;
	}

	Collision::Result Sphere3D::Check(const AABB3D* other) const
	{
		Collision::Result result = ::CheckAABBSphere(other, this);
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
		Vector3 minPos = this->GetWorldPos() - this->GetHalfSize();
		Vector3 maxPos = this->GetWorldPos() + this->GetHalfSize();

		DrawCube3D(minPos.GetAsDxLibVector(), maxPos.GetAsDxLibVector(), color.GetAsHexRGB(), color.GetAsHexRGB(), false);
	}

	Collision::Result AABB3D::Check(const Sphere3D* other) const
	{
		return ::CheckAABBSphere(this, other);
	}

	Collision::Result AABB3D::Check(const AABB3D* other) const
	{
		Collision::Result result;

		// 角の座標をキャッシュ
		Vector3 myMinPos = this->GetWorldPos() - this->GetHalfSize();
		Vector3 myMaxPos = this->GetWorldPos() + this->GetHalfSize();
		Vector3 otherMinPos = other->GetWorldPos() - other->GetHalfSize();
		Vector3 otherMaxPos = other->GetWorldPos() + other->GetHalfSize();

		// 衝突していないか計算
		if (myMinPos.x > otherMaxPos.x) return result;
		if (myMaxPos.x < otherMinPos.x) return result;

		if (myMinPos.y > otherMaxPos.y) return result;
		if (myMaxPos.y < otherMinPos.y) return result;

		if (myMinPos.z > otherMaxPos.z) return result;
		if (myMaxPos.z < otherMinPos.z) return result;

		result.isHit = true;

		// めり込み具合を計算
		CalculateBoxPenetrateVector(result, myMinPos, myMaxPos, otherMinPos, otherMaxPos);

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
		Vector3 center = GetWorldPos();

		Vector3 move = pos - center + mOffsetPos * 2.0f;

		mStartPos += move;
		mEndPos += move;
	}

	Vector3 Capsule3D::GetPosition() const
	{
		return (mStartPos + mEndPos) * 0.5f;
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
