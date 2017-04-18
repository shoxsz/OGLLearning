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
void normalize(Matrix<1, cols, dataType>& vec) {
	dataType norma = dataType();
	for (unsigned int i = 0; i < cols; i++) {
		norma += vec[i]*vec[i];
	}
	
	for (unsigned int i = 0; i < cols; i++) {
		vec[i] = vec[i] * vec[i] / norma;
	}
}




#endif