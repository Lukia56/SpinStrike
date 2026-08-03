#pragma once

#include <chrono>

class TimeManager
{
public:

	using clock = std::chrono::steady_clock;

	TimeManager() = delete;

	constexpr static float kFPS = 60.0f;

	static void Initialize();
	static void Update();

public:

	static float GetDeltaTime() { return mDeltaTime; }

	static long GetFixedDeltaTimeMs() { return mFixedDeltaTimeMs; }

	static float GetRawDeltaTime() { return mRawDeltaTime; }

	static float GetTimeScale() { return mTimeScale; }
	static float SetTimeScale(float timeScale) { mTimeScale = timeScale; }

	static clock::time_point GetPrevTime() { return mPrevTime; }

private:

	static float mDeltaTime;

	static long mFixedDeltaTimeMs;

	static float mRawDeltaTime;

	static float mTimeScale;

	static clock::time_point mPrevTime;
};
