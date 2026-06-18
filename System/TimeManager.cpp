#include "TimeManager.h"
#include "Utility/Math.h"

float TimeManager::mDeltaTime = 0.0f;
long TimeManager::mFixedDeltaTimeMs = (1.0f / TimeManager::kFPS) * 1000000;
float TimeManager::mRawDeltaTime = 0.0f;
float TimeManager::mTimeScale = 1.0f;
std::chrono::steady_clock::time_point TimeManager::mPrevTime = clock::now();

namespace
{
	// ゲーム中断時に大幅に時間が飛ばないようにする用
	constexpr float kMaxDeltaTime = 0.1f;
}

void TimeManager::Initialize()
{
	mPrevTime = clock::now();
}

void TimeManager::Update()
{
	using namespace std::chrono;

	// 現在の時間を取得
	clock::time_point currentTime = clock::now();

	// 経過時間を計算
	float deltaTime = duration<float>(currentTime - mPrevTime).count();
	mPrevTime = clock::now();

	// デバッグ等の確認環境による異常値を制限
	if (deltaTime > kMaxDeltaTime)
	{
		deltaTime = kMaxDeltaTime;
	}

	// 時間倍率適用前に保存
	mRawDeltaTime = deltaTime;
	mDeltaTime = deltaTime * mTimeScale;
}
