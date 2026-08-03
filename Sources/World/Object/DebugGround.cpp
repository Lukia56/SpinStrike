#include "DebugGround.h"
#include <DxLib.h>
#include "Utility/Color.h"
#include "Utility/Vector.h"

namespace
{
	constexpr float kAreaHalfSize = 1000.0f;

	constexpr float kLineDistance = 100.0f;

	constexpr int kLineNum = static_cast<int>((kAreaHalfSize * 2.0f) / kLineDistance);
}

void DebugGround::Draw()
{
	Vector3 centerPos = mTransform.CalculateWorldPosition();

	DrawXAxis(centerPos);
	DrawZAxis(centerPos);
}

void DebugGround::DrawXAxis(const Vector3& centerPos)
{
	Vector3 start, end;

	// XŽ²‚Ì’[‚ðŒvŽZ
	start = Vector3(centerPos.x - kAreaHalfSize, 0.0f, std::round((centerPos.z - kAreaHalfSize) / kLineDistance) * kLineDistance);
	end = Vector3(centerPos.x + kAreaHalfSize, 0.0f, std::round((centerPos.z - kAreaHalfSize) / kLineDistance) * kLineDistance);

	// XŽ²‚ð•`‰æ
	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(start.GetAsDxLibVector(), end.GetAsDxLibVector(), Color::red.GetAsHexRGB());

		start.z += kLineDistance;
		end.z += kLineDistance;

		if (start.x > centerPos.x + kAreaHalfSize) break;
	}
}

void DebugGround::DrawZAxis(const Vector3& centerPos)
{
	Vector3 start, end;

	// ZŽ²‚Ì’[‚ðŒvŽZ
	start = Vector3(std::round((centerPos.x - kAreaHalfSize) / kLineDistance) * kLineDistance, 0.0f, centerPos.z - kAreaHalfSize);
	end = Vector3(std::round((centerPos.x - kAreaHalfSize) / kLineDistance) * kLineDistance, 0.0f, centerPos.z + kAreaHalfSize);

	// ZŽ²‚ð•`‰æ
	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(start.GetAsDxLibVector(), end.GetAsDxLibVector(), Color::blue.GetAsHexRGB());

		start.x += kLineDistance;
		end.x += kLineDistance;

		if (start.x > centerPos.x + kAreaHalfSize) break;
	}
}
