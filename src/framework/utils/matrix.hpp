#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <array>
#include <stdexcept>

/*Matrizes e vetores

	Nesse framework vetores são armazenados como matrizes, o arquivo vector.hpp
	possui funcionalidades para tratar das individualidades dos vetores, esse arquivo
	implementa uma classe de matriz genérica  e fornece funções para matrizes específicas:
		matrizes de transformação e matrizes de perspectiva(4x4)
*/

template<unsigned int rows, unsigned int columns, class dataType = float>
class Matrix{
public:
    typedef Matrix<rows, columns, dataType> MyMatrix;
    typedef Matrix<columns, rows, dataType> MyTranspost;

    Matrix(){
        matrix.fill(0);
    }

    Matrix(std::initializer_list<dataType> list){
        set(list);
    }

    MyTranspost transpose(){
        unsigned int line, m_line;
        MyTranspost transpost;

        for(unsigned int i = 0; i < columns; i++){
            line = i * columns;
            for(unsigned int j = 0; j < rows; j++){
                m_line = j * columns;
                transpost.matrix[line + j] = matrix[m_line + i];
            }
        }

        return transpost;
    }

    void set(const dataType* matrix){
        unsigned int elems = columns * rows;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] = matrix;
        }
    }

    void set(std::initializer_list<dataType> list){
        auto list_it = list.begin();
        unsigned int elems = rows * columns;
        for(unsigned int i = 0; i < elems; i++, list_it++){
            matrix[i] = *list_it;
        }
    }

	void loadIdentity() {
		matrix.fill(0);
		for (unsigned int i = 0; i < columns; i++) {
			matrix[i * columns + i] = 1;
		}
	}

    void scale(const dataType& scalar){
        unsigned int elems = rows * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] *= scalar;
        }
    }

    void sum(const MyMatrix& matrix){
        unsigned int elems = rows * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] += matrix.matrix[i];
        }
    }

    void sub(const MyMatrix& matrix){
        unsigned int elems = rows * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] -= matrix.matrix[i];
        }
    }

    template<unsigned int _rows = rows, unsigned int _columns = columns>
    Matrix<rows, _columns, dataType> mult(Matrix<_rows, _columns, dataType>& matrix)const{
        Matrix<rows, _columns, dataType> result;

        if(columns != _rows)
            throw std::invalid_argument("Matrices informed can't be multiplied!'");
        
        for(unsigned int i = 0; i < rows; i++){
			for (unsigned int j = 0; j < _columns; j++) {
				for (unsigned int k = 0; k < columns; k++) {
					result[i][j] += (*this)[i][k] * matrix[k][j];
				}
			}
        }

        return result;
    }

	const dataType* get()const { return matrix.data(); }

    MyMatrix operator*(const dataType& scalar)const{
        MyMatrix result(*this);

        result.scale(scalar);
        return result;
    }

    void operator*=(const dataType& scalar){
        scale(scalar);
    }

    MyMatrix& operator+(const MyMatrix& matrix)const{
        MyMatrix result(*this);

        result.add(matrix);
        return result;
    }

    void operator+=(const MyMatrix& matrix){
        add(matrix);
    }

    MyMatrix& operator-(const MyMatrix& matrix)const{
        MyMatrix result(*this);

        result.sub(matrix);
        return result;
    }

    void operator-=(const MyMatrix& matrix){
        sub(matrix);
    }

    const dataType* operator[](unsigned int row)const{
        return matrix.data() + (row * columns);
    }

    dataType* operator[](unsigned int row){
        return matrix.data() + (row * columns);
    }

private:
    std::array<dataType, rows * columns> matrix;
};

typedef Matrix<2, 2, int> Mat2x2;
typedef Matrix<3, 3, int> Mat3x3;
typedef Matrix<4, 4, int> Mat4x4;

typedef Matrix<2, 2, float> Mat2x2f;
typedef Matrix<3, 3, float> Mat3x3f;
typedef Matrix<4, 4, float> Mat4x4f;

Mat4x4f perspective(float fovy, float ratio, float n, float f);
Mat4x4f perspective(float l, float r, float b, float t, float n, float f);
Mat4x4f orthographic(float l, float r, float b, float t, float n, float f);
Mat4x4f translate(float x, float y, float z);
Mat4x4f rotate(float angle, float x, float y, float z);
Mat4x4f scale(float scale);
Mat4x4f lookAt(
	const Matrix<1, 3, float>& eye, 
	const Matrix<1, 3, float>& center,
	const Matrix<1, 3>& up);

#endif