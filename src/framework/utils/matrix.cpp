#include "matrix.hpp"

#include <cmath>

Mat4x4f perspective(float l, float r, float b, float t, float n, float f) {
	return {
		(2 * n) / (l - r), 0, (2 * (r + l)) / (r - l), 0,
		0, 2 * n / (t - b), (2 * (t + b)) / (t - b), 0,
		0, 0, (-1 * (f + n)) / (f - n), (2 * f * n) / (f - n),
		0, 0, -1, 0
	};
}

Mat4x4f ortographic(float l, float r, float b, float t, float n, float f) {
	return {
		1 / (r - l)/2, 0, 0, -(r + l)/(r - l),
		0, 1 / (t - b)/2, 0, -(t + b)/(t - b),
		0, 0, 1 / (f - n)/2, -(f + n)/(f - n),
		0, 0, 0, 1
	};
}

Mat4x4f translate(float x, float y, float z) {
	return {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

Mat4x4f rotate(float angle, float x, float y, float z) {
	float pi = std::acos(-1);
	
	angle = pi * angle / 180.0f;

	float cos = std::cos(angle);
	float sin = std::sin(angle);

	return {
		cos + x*x*(1 - cos), x*y*(1 - cos) - z*sin, x*z*(1 - cos) - y*sin, 0,
		y*x*(1 - cos) + z*sin, cos + y*y*(1 - cos), y*z*(1 - cos) - x*sin, 0,
		z*x*(1 - cos) + y*sin, y*z*(1 - cos) + x*sin, cos + z*z*(1 - cos), 0,
		0, 0, 0, 1
	};
}

Mat4x4f scale(float scale) {
	return {
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1
	};
}