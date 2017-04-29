#include "matrix.hpp"

#include <cmath>

#include "vector.hpp"

Mat4x4f perspective(float fovy, float ratio, float n, float f) {
	float tan = std::tanf(fovy);
	float height = 2 * tan * n;
	float width = height*ratio;
	return perspective(-width/2, width/2, -height/2, height/2, n, f);
}

Mat4x4f perspective(float l, float r, float b, float t, float n, float f) {
	return {
		2*n/(r - l), 0, (r+l)/(r-l), 0,
		0, 2*n/(t-b), (t+b)/(t-b), 0,
		0, 0, -(f+n)/(f-n), -2*f*n/(f-n),
		0, 0, -1, 0
	};
}

Mat4x4f orthographic(float l, float r, float b, float t, float n, float f) {
	return {
		1 / (r - l)/2, 0, 0, -(r + l)/(r - l),
		0, 1 / (t - b)/2, 0, -(t + b)/(t - b),
		0, 0, 1 / (f - n)/2, -(f + n)/(f - n),
		0, 0, 0, 1
	};
}

Mat4x4f translate(float x, float y, float z) {
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};
}

Mat4x4f rotate(float angle, float x, float y, float z) {
	float pi = std::acos(-1);
	
	angle = pi * angle / 180.0f;

	float cos = std::cos(angle);
	float sin = std::sin(angle);

	return{
		cos + x*x*(1 - cos), y*x*(1 - cos) + z*sin, z*x*(1 - cos) + y*sin, 0,
		x*y*(1 - cos) - z*sin, cos + y*y*(1 - cos), y*z*(1 - cos) + x*sin, 0,
		x*z*(1 - cos) - y*sin, y*z*(1 - cos) - x*sin, cos + z*z*(1 - cos), 0,
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

Mat4x4f lookAt(
	const Matrix<1, 3, float>& eye,
	const Matrix<1, 3, float>& center,
	const Matrix<1, 3, float>& up) {
	//forward vector
	Matrix<1, 3, float> f(normalize<3, float>(center - eye));
	//left vector
	Matrix<1, 3, float> s(normalize<3, float>(cross_product(f, up)));
	//up vector
	Matrix<1, 3, float> u(cross_product(s, f));

	return {
		s[0][0], s[0][1], s[0][2], 0.0f,
		u[0][0], u[0][1], u[0][2], 0.0f,
		-f[0][0], u[0][1], -f[0][2], 0.0f,
		eye[0][0], eye[0][1], eye[0][2], 1.0f
	};
}