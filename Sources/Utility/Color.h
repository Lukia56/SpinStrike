#pragma once

#include <span>

/// <summary>
/// RGBAを0.0f～1.0fで持つ構造体
/// </summary>
struct Color
{
	// 色
	float r, g, b, a;

	/// <summary>
	/// 各色を0で初期化
	/// </summary>
	constexpr Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

	/// <summary>
	/// 各色を指定して初期化
	/// アルファは1で初期化する
	/// </summary>
	/// <param name="r">赤</param>
	/// <param name="g">緑</param>
	/// <param name="b">青</param>
	constexpr Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}

	/// <summary>
	/// 各色を指定して初期化
	/// アルファも指定して初期化
	/// </summary>
	/// <param name="r">赤</param>
	/// <param name="g">緑</param>
	/// <param name="b">青</param>
	/// <param name="a">アルファ</param>
	constexpr Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	// ヘルパー関数

	/// <summary>
	/// RGBをfloatの配列として取得
	/// アルファを含めない
	/// </summary>
	constexpr std::span<const float, 3> GetAsFloatPointerRGB() const
	{
		float color[] = { r, g, b };
		return color;
	}
	/// <summary>
	/// RGBAをfloatの配列として取得
	/// アルファを含める
	/// </summary>
	constexpr std::span<const float, 4> GetAsFloatPointerRGBA() const
	{
		float color[] = { r, g, b, a };
		return color;
	}

	/// <summary>
	/// RGBを16進数として取得
	/// アルファを含めない
	/// </summary>
	constexpr unsigned int GetAsHexRGB() const
	{
		// 16進数に変換
		unsigned int red = static_cast<unsigned int>(r * 65536);	// 2 ^ 16
		unsigned int green = static_cast<unsigned int>(g * 256);	// 2 ^ 8
		unsigned int blue = static_cast<unsigned int>(b);			// 2 ^ 0

		unsigned int color = (red + green + blue) * 255;

		return color;
	}
	/// <summary>
	/// RGBAを16進数として取得
	/// アルファを含める
	/// </summary>
	constexpr unsigned int GetAsHexRGBA() const
	{
		// 16進数に変換
		unsigned int red = static_cast<unsigned int>(r * 16777216);	// 2 ^ 24
		unsigned int green = static_cast<unsigned int>(g * 65536);	// 2 ^ 16
		unsigned int blue = static_cast<unsigned int>(b * 256);		// 2 ^ 8
		unsigned int alpha = static_cast<unsigned int>(a);			// 2 ^ 0

		unsigned int color = (red + green + blue + alpha) * 255;

		return color;
	}

	// 定数

	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color cyan;
	static const Color magenta;
	static const Color yellow;
	static const Color black;
	static const Color white;
	static const Color gray;
};
