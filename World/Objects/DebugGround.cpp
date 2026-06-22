#include "DebugGround.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "Utility/Vector.h"

namespace
{
	constexpr float kAreaHalfSize = 1000.0f;

	constexpr float kLineDistance = 100.0f;

	constexpr int kLineNum = (kAreaHalfSize * 2.0f) / kLineDistance;
}

void DebugGround::Draw()
{
	Vector3 pos = mTransform.CalculateWorldPosition();

	Vector3 start, end;

	start	= Vector3(pos.x - kAreaHalfSize, 0.0f, std::round((pos.z - kAreaHalfSize) * 0.01f) * 100);
	end		= Vector3(pos.x + kAreaHalfSize, 0.0f, std::round((pos.z - kAreaHalfSize) * 0.01f) * 100);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(start.GetAsDxLibVector(), end.GetAsDxLibVector(), Color::red.GetAsHexRGB());

		start.z += kLineDistance;
		end.z += kLineDistance;

		if (start.x > pos.x + kAreaHalfSize) break;
	}

	start	= Vector3(std::round((pos.x - kAreaHalfSize) * 0.01f) * 100, 0.0f, pos.z - kAreaHalfSize);
	end		= Vector3(std::round((pos.x - kAreaHalfSize) * 0.01f) * 100, 0.0f, pos.z + kAreaHalfSize);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(start.GetAsDxLibVector(), end.GetAsDxLibVector(), Color::blue.GetAsHexRGB());

		start.x += kLineDistance;
		end.x += kLineDistance;

		if (start.x > pos.x + kAreaHalfSize) break;
	}
}
