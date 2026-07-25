#pragma once

#include "Vector.h"

namespace Geometry
{
	bool IsSharpAngle(const Vector3& a, const Vector3& b, const Vector3& c)
	{
		Vector3 ab = b - a;
		Vector3 cb = b - c;
		return ab.Dot(cb) > 0.0f;
	}

	float CalculatePointSegmentSqDistance(const Vector3& point, const Vector3& segStart, const Vector3& segEnd)
	{
		if (!Geometry::IsSharpAngle(point, segStart, segEnd))
		{
			return (point - segStart).GetSqLength();
		}
		else
		if (!Geometry::IsSharpAngle(point, segEnd, segStart))
		{
			return (point - segEnd).GetSqLength();
		}
		else
		{
			Vector3 segVec = segEnd - segStart;

			// 直線の方向ベクトルを取得
			Vector3 lineVec = segVec.GetNormalize();

			float t = 0.0f;
			if (segVec != Vector3::Zero)
			{
				 t = lineVec.Dot(point - segStart);
			}

			// 点から直線に下した垂線の足の座標を求める
			Vector3 h = segStart + lineVec * t;

			// 垂線の足と点の距離を最短距離にする
			return (point - h).GetSqLength();
		}
	}
}
