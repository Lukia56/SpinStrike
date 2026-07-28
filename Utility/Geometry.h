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

	Vector3 CalculatePointSegmentDistance(const Vector3& point, const Vector3& segStart, const Vector3& segEnd)
	{
		if (!Geometry::IsSharpAngle(point, segStart, segEnd))
		{
			return point - segStart;
		}
		else
		if (!Geometry::IsSharpAngle(point, segEnd, segStart))
		{
			return point - segEnd;
		}
		else
		{
			Vector3 segVec = segEnd - segStart;

			float segSqLength = segVec.GetSqLength();

			float t = 0.0f;
			if (segVec != Vector3::Zero)
			{
				t = segVec.Dot(point - segStart) / segSqLength;
			}

			// “_‚©‚çü•ª‚É‰º‚µ‚½‚ü‚Ì‘«‚ÌÀ•W‚ğ‹‚ß‚é
			Vector3 h = segStart + segVec * t;

			// ‚ü‚Ì‘«‚Æ“_‚Ì‹——£‚ğÅ’Z‹——£‚É‚·‚é
			return point - h;
		}
	}
}
