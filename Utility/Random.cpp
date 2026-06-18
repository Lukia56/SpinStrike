#include "Random.h"
#include <random>

void Random::Init()
{
	// シード値を設定
	Engine().seed(std::random_device{}());
}

float Random::Get0To1()
{
	return Range<float>(0.0f, 1.0f);
}

bool Random::Judge(float percent)
{
	return (Range<float>(0.0f, 100.0f) < percent);
}

std::mt19937& Random::Engine()
{
	static std::mt19937 engine{ std::random_device{}() };
	return engine;
}
