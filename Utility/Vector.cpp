#include "Vector.h"
#include <cassert>
#include <cmath>
#include <DxLib.h>
#include "Math.h"

// Vector2
const Vector2 Vector2::Zero			= Vector2(0.0f, 0.0f);
const Vector2 Vector2::One			= Vector2(1.0f, 1.0f);
const Vector2 Vector2::XAxis		= Vector2(1.0f, 0.0f);
const Vector2 Vector2::NegaXAxis	= Vector2(-1.0f, 0.0f);
const Vector2 Vector2::YAxis		= Vector2(0.0f, 1.0f);
const Vector2 Vector2::NegaYAxis	= Vector2(0.0f, -1.0f);

// Vector3
const Vector3 Vector3::Zero			= Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One			= Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::XAxis		= Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NegaXAxis	= Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis		= Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::NegaYAxis	= Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::ZAxis		= Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NegaZAxis	= Vector3(0.0f, 0.0f, -1.0f);

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float s) const
{
	return Vector2(x * s, y * s);
}

Vector2 Vector2::operator/(const float s) const
{
	if (s == 0.0f)
	{
		assert(false && "Vector2 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return Vector2::Zero;
	}

	return Vector2(x / s, y / s);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

Vector2& Vector2::operator*=(const float s)
{
	x *= s;
	y *= s;

	return *this;
}

Vector2& Vector2::operator/=(const float s)
{
	if (s == 0.0f)
	{
		assert(false && "Vector2 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return *this;
	}

	x /= s;
	y /= s;

	return *this;
}

float Vector2::operator[](int index) const
{
	return *(&x + index);
}

bool Vector2::operator==(const Vector2& v) const
{
	return Math::NearyEqual(x, v.x) && Math::NearyEqual(y, v.y);
}

bool Vector2::operator!=(const Vector2& v) const
{
	return !Math::NearyEqual(x, v.x) || !Math::NearyEqual(y, v.y);
}

float Vector2::Dot(const Vector2& v) const
{
	return (x * v.x) + (y * v.y);
}

float Vector2::Cross(const Vector2& v) const
{
	return (x * v.y) - (y * v.x);
}

float Vector2::GetLength() const
{
	return std::sqrt(GetSqLength());
}

float Vector2::GetSqLength() const
{
	return x * x + y * y;
}

Vector2 Vector2::GetNormalize() const
{
	if (*this == Vector2::Zero)
	{
		assert(false && "Vector2 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return Vector2::Zero;
	}

	return *this / GetLength();
}

inline VECTOR Vector2::GetAsDxLibVector() const
{
	return VGet(x, y, 0.0f);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const float s) const
{
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(const float s) const
{
	if (s == 0.0f)
	{
		assert(false && "Vector3 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return Vector3::Zero;
	}

	return Vector3(x / s, y / s, z / s);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3& Vector3::operator*=(const float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vector3& Vector3::operator/=(const float s)
{
	if (s == 0.0f)
	{
		assert(false && "Vector3 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return *this;
	}

	x /= s;
	y /= s;
	z /= s;

	return *this;
}

float Vector3::operator[](int index) const
{
	return *(&x + index);
}

bool Vector3::operator==(const Vector3& v) const
{
	return x == v.x && y == v.y && z == v.z;
}
bool Vector3::operator!=(const Vector3& v) const
{
	return x != v.x || y != v.y || z != v.z;
}

float Vector3::Dot(const Vector3& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector3 Vector3::Cross(const Vector3& v) const
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

float Vector3::GetLength() const
{
	return std::sqrt(GetSqLength());
}

float Vector3::GetSqLength() const
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::GetNormalize() const
{
	if (*this == Vector3::Zero)
	{
		assert(false && "Vector3 // 0èúéZÇ™çsÇÌÇÍÇ‹ÇµÇΩ");
		return Vector3::Zero;
	}

	return *this / GetLength();
}

VECTOR Vector3::GetAsDxLibVector() const
{
	return VGet(x, y, z);
}
