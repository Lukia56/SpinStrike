#include "InputDeviceBase.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <unordered_map>
#include "../Format/InputFormatBase.h"
#include "../Literal/KeyCodes.h"
#include "Utility/Math.h"
#include "Utility/Vector.h"

namespace
{
	constexpr int kMaxLog = 65535;
	constexpr int kMinLog = -65535;
}

InputDeviceBase::InputDeviceBase() = default;

InputDeviceBase::~InputDeviceBase() = default;

void InputDeviceBase::Init()
{
	InitDevice();

	// 押下時間をリセット
	for (const auto& format : mFormats)
	{
		for (const auto& keyCode : format->GetLinkToKeyCode())
		{
			mPressedFrameLogs.emplace(keyCode.first, 0);
		}
	}
}
void InputDeviceBase::Update()
{
	for (const auto& format : mFormats)
	{
		for (const auto& keyCode : format->GetLinkToKeyCode())
		{
			UpdatePressedFrame(format.get(), keyCode.first);
		}
	}
}

bool InputDeviceBase::IsDown(KeyCode::Button keyCode) const
{
	return mPressedFrameLogs.at(keyCode) > 0;
}

bool InputDeviceBase::IsPressed(KeyCode::Button keyCode) const
{
	return mPressedFrameLogs.at(keyCode) == 1;
}

bool InputDeviceBase::IsReleased(KeyCode::Button keyCode) const
{
	return mPressedFrameLogs.at(keyCode) == -1;
}

bool InputDeviceBase::IsHeld(KeyCode::Button keyCode, int frame) const
{
	if (frame > 0) return mPressedFrameLogs.at(keyCode) >= frame;
	else return mPressedFrameLogs.at(keyCode) <= frame;
}

Vector3 InputDeviceBase::GetValue(KeyCode::Button keyCode) const
{
	for (const auto& format : mFormats)
	{
		auto linker = format->GetLinkToKeyCode();

		// フォーマットに調べたいキーコードが含まれていなかったらスキップ
		auto iter = linker.find(keyCode);
		if (iter == linker.end()) continue;

		return format->GetValue(keyCode);
	}

	return Vector3::Zero;
}

void InputDeviceBase::UpdatePressedFrame(InputFormatBase* format, KeyCode::Button keyCode)
{
	int frame = mPressedFrameLogs.at(keyCode);

	// 押されていたら
	if (format->CheckButtonState(keyCode))
	{
		// 前のフレームで押されていなかったらカウントを0にする
		frame = Math::Max(0, frame);

		// カウントアップ
		frame++;
	}
	else
	{
		// 今まで押されたことが無かったらスキップ
		if (frame == 0) return;

		// 前のフレームで押されていたらカウントを0にする
		frame = Math::Min(0, frame);

		// カウントダウン
		frame--;
	}

	// オーバーフロー・アンダーフロー対策で値を収める
	frame = Math::Clamp(frame, kMinLog, kMaxLog);

	mPressedFrameLogs.at(keyCode) = frame;
}
