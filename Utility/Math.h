#pragma once

#include <cmath>
#include <numbers>
#include "Vector.h"

namespace Math
{
	// 円周率 | 180度
	constexpr float kPi = std::numbers::pi_v<float>;
	// 円周率 x 2 | 360度
	constexpr float k2Pi = kPi * 2.0f;
	// 円周率 / 2 | 90度
	constexpr float kPiOver2 = kPi / 2.0f;

	// 小数の誤差許容範囲
	constexpr float Epsilon = 0.00001f;

	template <std::floating_point T>
	constexpr T ToRadian(const T degree)
	{
		return degree * kPi / 180.0f;
	}
	template <std::floating_point T>
	constexpr T ToDegree(const T radian)
	{
		return radian * 180.0f / kPi;
	}
	/// <summary>
	/// デグリー角を180度～-180度の間に収める
	/// </summary>
	template <std::floating_point T>
	constexpr T NormalizeDegree(T degree)
	{
		while (degree > 180.0f) degree -= 360.0f;
		while (degree < -180.0f) degree += 360.0f;

		return degree;
	}
	/// <summary>
	/// ラジアン角を180度～-180度の間に収める
	/// </summary>
	template <std::floating_point T>
	constexpr T NormalizeRadian(T radian)
	{
		while (radian > Math::kPi) radian -= Math::k2Pi;
		while (radian < -Math::kPi) radian += Math::k2Pi;

		return radian;
	}

	template <typename T>
	constexpr T Max(const T a, const T b)
	{
		return (a > b ? a : b);
	}
	template <typename T>
	constexpr T Min(const T a, const T b)
	{
		return (a > b ? b : a);
	}
	template <typename T>
	constexpr T Clamp(const T value, const T min, const T max)
	{
		return Math::Min(Math::Max(value, min), max);
	}

	/// <summary>
	/// 符号を取得する
	/// </summary>
	/// <returns>正 -> 1 | 負 -> -1 | 0 -> 0</returns>
	template <typename T>
	constexpr int Sign(const T value)
	{
		return (value > 0) - (value < 0);
	}

	/// <summary>
	/// 累乗した値を計算する
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="n">掛ける数（自然数のみ）</param>
	template <typename T>
	constexpr T Pow(const T value, const int n)
	{
		if (n <= 0) return 0.0f;

		T result = 0.0f;
		for (int i = 0; i < n; i++)
		{
			result *= value;
		}
		return result;
	}
	/// <summary>
	/// 2乗した値を計算する
	/// </summary>
	template <typename T>
	constexpr T Sqr(const T value)
	{
		return value * value;
	}

	template <std::floating_point T>
	constexpr T Leap(const T a, const T b, const T t)
	{
		return a + (b - a) * t;
	}
	template <std::floating_point T>
	constexpr T LerpDelta(const T a, const T b, const T t, const float delta)
	{
		T time = Math::Clamp(t * delta, 0.0f, 1.0f);
		return a + (b - a) * time;
	}
	template <typename T>
	constexpr T Approach(const T src, const T dst, const T change)
	{
		if (src > dst)
		{
			return Math::Max(src - change, dst);
		}
		else
		{
			return Math::Min(src + change, dst);
		}
	}

	/// <summary>
	/// 誤差込みで0と等しいと言えるかどうか
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="epsilon">許容範囲</param>
	template <std::floating_point T>
	constexpr bool IsNearZero(const T value, const float epsilon = Epsilon)
	{
		if (std::abs(value) <= epsilon) return true;

		return false;
	}
	/// <summary>
	/// 誤差込みで等しいと言えるかどうか
	/// 浮動小数点数の丸め誤差対策
	/// </summary>
	/// <param name="a">値1</param>
	/// <param name="b">値2</param>
	/// <param name="epsilon">許容範囲</param>
	template <std::floating_point T>
	constexpr bool NearyEqual(const T a, const T b, const float epsilon = Epsilon)
	{
		if (std::abs(a - b) <= epsilon) return true;

		return false;
	}

	/// <summary>
	/// 1D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	/// <param name="axis">軸</param>
	/// <param name="maxValue">最大値</param>
	/// <param name="deadzoneMin">デッドゾーンの最小割合</param>
	/// <param name="deadzoneMax">デッドゾーンの最大割合</param>
	/// <returns>デッドゾーンを適用して正規化した軸</returns>
	inline float Filter1D(int axis, int maxValue, float deadzoneMin, float deadzoneMax)
	{
		// デッドゾーンをmaxValueの割合に変換
		const int dzMin = static_cast<int>(maxValue * deadzoneMin);
		const int dzMax = static_cast<int>(maxValue * deadzoneMax);

		// 計算しやすくするために絶対値を取得する
		const int absAxis = std::abs(axis);

		float result = 0.0f;

		// デッドゾーンより小さい入力なら0とする
		if (absAxis < dzMin) return result;

		// デッドゾーンの最小値と最大値の間の割合を取得する
		result = static_cast<float>(absAxis - dzMin) / static_cast<float>(dzMax - dzMin);

		// 符号を復元する
		result *= Math::Sign(axis);

		// 値を-1から1に収める
		result = Math::Clamp(result, -1.0f, 1.0f);

		return result;
	}

	/// <summary>
	/// 2D軸の値をデッドゾーン内の割合にフィルタリングする
	/// </summary>
	/// <param name="axisX">軸X</param>
	/// <param name="axisY">軸Y</param>
	/// <param name="maxValue">最大値</param>
	/// <param name="deadzoneMin">デッドゾーンの最小割合</param>
	/// <param name="deadzoneMax">デッドゾーンの最大割合</param>
	/// <returns>デッドゾーンを適用して正規化した軸</returns>
	inline Vector2 Filter2D(float axisX, float axisY, float maxValue, float deadzoneMin, float deadzoneMax)
	{
		// デッドゾーンをmaxValueの割合に変換
		const float dzMin = maxValue * deadzoneMin;
		const float dzMax = maxValue * deadzoneMax;

		// ベクトルに変換
		const Vector2 dir = Vector2(axisX, axisY);

		const float len = dir.GetLength();

		Vector2 result = Vector2::Zero;

		// デッドゾーンより小さい入力なら0とする
		if (len < dzMin) return result;

		// デッドゾーンの最小値と最大値の間の割合を取得する
		float rate = (len - dzMin) / (dzMax - dzMin);

		// 値を0から1に収める
		rate = Math::Clamp(rate, 0.0f, 1.0f);

		// スケーリング
		result = dir * (rate / len);

		return result;
	}
}
