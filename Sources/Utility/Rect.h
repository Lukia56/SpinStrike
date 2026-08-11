#pragma once

struct Rect
{
	float xMin;
	float yMin;
	float width;
	float height;

	constexpr Rect() : xMin(0.0f), yMin(0.0f), width(0.0f), height(0.0f) {}
	constexpr Rect(float left, float top, float right, float bottom) : xMin(left), yMin(top), width(right), height(bottom) {}
};
