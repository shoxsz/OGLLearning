#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "matrix.hpp"

typedef Matrix<1, 2, int> Vec2;
typedef Matrix<1, 3, int> Vec3;
typedef Matrix<1, 4, int> Vec4;

typedef Matrix<1, 2, float> Vec2f;
typedef Matrix<1, 3, float> Vec3f;
typedef Matrix<1, 4, float> Vec4f;

template <unsigned int cols = 4, typename dataType = float>
Matrix<1, cols, dataType> normalize(Matrix<1, cols, dataType> vec) {
	dataType norma = dataType();
	Matrix<1, cols, dataType> vec_n;

	for (unsigned int i = 0; i < cols; i++) {
		norma += vec[0][i] * vec[0][i];
	}

	norma = std::sqrtf(norma);
	for (unsigned int i = 0; i < cols; i++) {
		vec_n[0][i] = vec[0][i] / norma;
	}

	return vec_n;
}

//por enquanto só calcula o produto cruzado de vetores 3
template<unsigned int cols = 3, typename dataType = float>
Matrix<1, cols> cross_product(
	const Matrix<1, cols, dataType>& v1,
	const Matrix<1, cols, dataType>& v2) {
	if (cols == 3) {
		return {
			(v1[0][1] * v2[0][2] - v1[0][2] * v2[0][1]),
			-(v1[0][0] * v2[0][2] - v1[0][2] * v2[0][0]),
			(v1[0][0] * v2[0][1] - v1[0][1] * v2[0][0])
		};
	}

	return {};
}

template<unsigned int cols = 4, typename dataType = float>
dataType dot_product(
	const Matrix<1, cols, dataType>& v1,
	const Matrix<1, cols, dataType>& v2) {
	dataType result = dataType();

	for (unsigned int i = 0; i < cols; i++) {
		result += v1[0][i] * v2[0][i];
	}

	return result;
}
#endif