#include "DebugGround.h"
#include <DxLib.h>
#include "Utility/Color.h"

namespace
{
	constexpr float kLineAreaSize = 10000.0f;

	constexpr int kLineNum = 50;
}

void DebugGround::Draw()
{
	VECTOR pos1;
	VECTOR pos2;

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(-kLineAreaSize / 2.0f, 0.0f, kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1, pos2, Color::white.GetAsHexRGB());
		pos1.x += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.x += kLineAreaSize / static_cast<float>(kLineNum);
	}

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1, pos2, Color::white.GetAsHexRGB());
		pos1.z += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.z += kLineAreaSize / static_cast<float>(kLineNum);
	}
}
