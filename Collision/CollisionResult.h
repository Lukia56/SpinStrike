#pragma once

#include "Utility/Vector.h"

namespace Collision
{
	/// <summary>
	/// 衝突結果のデータ群
	/// </summary>
	struct Result
	{
		bool isHit = false;

		/// <summary>
		/// 衝突した面の法線
		/// </summary>
		Vector3 normal = Vector3::Zero;

		/// <summary>
		/// めりこみ具合
		/// </summary>
		float penetration = 0.0f;
	};
}