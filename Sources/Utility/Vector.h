#pragma once

#include <DxLib.h>

struct Vector2
{
	float x, y;

	/// <summary>
	/// 各成分を0で初期化
	/// </summary>
	constexpr Vector2() : x(0.0f), y(0.0f) {};

	/// <summary>
	/// 各成分を指定して初期化
	/// </summary>
	constexpr Vector2(float x, float y) : x(x), y(y) {};

	// 演算子

	Vector2 operator-() const;

	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const float s) const;
	Vector2 operator/(const float s) const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(const float s);
	Vector2& operator/=(const float s);

	float operator[](int index) const;

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	// ヘルパー関数

	/// <summary>
	/// 内積を計算する
	/// </summary>
	float Dot(const Vector2& v) const;

	/// <summary>
	/// 外積を計算する
	/// </summary>
	float Cross(const Vector2& v) const;

	/// <summary>
	/// ベクトルの長さを取得する
	/// 処理が重いため非推奨
	/// </summary>
	float GetLength() const;

	/// <summary>
	/// ベクトルの長さの2乗を取得する
	/// </summary>
	float GetSqLength() const;

	/// <summary>
	/// 正規化したベクトルを取得する
	/// </summary>
	Vector2 GetNormalize() const;

	/// <summary>
	/// DxLibのベクトルに変換する
	/// </summary>
	VECTOR GetAsDxLibVector() const;

	// 定数

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 XAxis;
	static const Vector2 NegaXAxis;
	static const Vector2 YAxis;
	static const Vector2 NegaYAxis;
};

struct Vector3
{
	float x, y, z;

	/// <summary>
	/// 各成分を0で初期化
	/// </summary>
	constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	/// <summary>
	/// 各成分を指定して初期化
	/// </summary>
	constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

	// 演算子

	Vector3 operator-() const;

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float s) const;
	Vector3 operator/(const float s) const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const float s);
	Vector3& operator/=(const float s);

	float operator[](int index) const;

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	// ヘルパー関数

	/// <summary>
	/// 内積を計算する
	/// </summary>
	float Dot(const Vector3& v) const;

	/// <summary>
	/// 外積を計算する
	/// </summary>
	Vector3 Cross(const Vector3& v) const;

	/// <summary>
	/// ベクトルの長さを取得する
	/// 処理が重いため非推奨
	/// </summary>
	float GetLength() const;

	/// <summary>
	/// ベクトルの長さの2乗を取得する
	/// </summary>
	float GetSqLength() const;

	/// <summary>
	/// 正規化したベクトルを取得する
	/// </summary>
	Vector3 GetNormalize() const;

	/// <summary>
	/// DxLibのベクトルに変換する
	/// </summary>
	VECTOR GetAsDxLibVector() const;

	// 定数

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 XAxis;
	static const Vector3 NegaXAxis;
	static const Vector3 YAxis;
	static const Vector3 NegaYAxis;
	static const Vector3 ZAxis;
	static const Vector3 NegaZAxis;
};
