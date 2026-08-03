#pragma once

#include <random>

/// <summary>
/// 乱数を生成するクラス
/// </summary>
class Random
{
public:

	/// <summary>
	/// シード値の初期化を行う
	/// </summary>
	static void Init();

	/// <summary>
	/// 引数の範囲内での整数乱数を生成
	/// </summary>
	/// <param name="minInclude">最小値（含む）</param>
	/// <param name="maxExclude">最大値（含まない）</param>
	template <std::integral T>
	static T Range(T minInclude, T maxExclude);

	/// <summary>
	/// 引数の範囲内での実数乱数を生成
	/// </summary>
	/// <param name="minInclude">最小値（含む）</param>
	/// <param name="maxInclude">最大値（含む）</param>
	template <std::floating_point T>
	static T Range(T minInclude, T maxInclude);

	/// <summary>
	/// 0.0～1.0の実数の乱数生成
	/// </summary>
	static float Get0To1();

	/// <summary>
	/// 確率判定
	/// </summary>
	/// <param name="percent">確率0～100</param>
	/// <returns>確率内ならtrue</returns>
	static bool Judge(float percent);

private:

	/// <summary>
	/// 乱数を生成する
	/// </summary>
	static std::mt19937& Engine();
};

template<std::integral T>
inline T Random::Range(T minInclude, T maxExclude)
{
	std::uniform_int_distribution<T> dist(minInclude, maxExclude - 1);
	return dist(Engine());
}

template<std::floating_point T>
inline T Random::Range(T minInclude, T maxInclude)
{
	std::uniform_real_distribution<T> dist(minInclude, maxInclude);
	return dist(Engine());
}
