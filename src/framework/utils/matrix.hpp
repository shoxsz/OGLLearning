#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <array>
#include <stdexcept>

template<typename dataType = float, unsigned int columns = 2, unsigned int rows = 2>
class Matrix{
public:
    typedef Matrix<dataType, columns, rows> MyMatrix;
    typedef Matrix<dataType, rows, columns> MyTranspost;

    Matrix(bool loadIdentity = true){ 
        if(loadIdentity)
            this->loadIdentity();
        else
            matrix->fill(0);
    }

    void loadIdentity(){
        matrix.fill(0);
        for(unsigned int i = 0; i < columns; i++;){
            matrix[i * columns + i] = 1;
        }
    }

    MyTranspost transpose(){
        unsigned int line, m_line;
        MyTranspost transpost(false);

        for(unsigned int i = 0; i < columns; i++){
            line = i * columns;
            for(unsigned int j = 0; j < rows; j++){
                m_line = j * columns;
                transpost.matrix[line + j] = matrix[m_line + i];
            }
        }

        return transpost;
    }

    void set(dataType* matrix){
        unsigned int elems = columns * rows;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] = matrix;
        }
    }

    const dataType* get()const{ return matrix.data(); }

    void scale(const dataType& scalar){
        unsigned int elems = row * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] *= scalar;
        }
    }

    void add(const MyMatrix& matrix){
        unsigned int elems = row * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] += matrix.matrix[i];
        }
    }

    void sub(const MyMatrix& matrix){
        unsigned int elems = row * columns;
        for(unsigned int i = 0; i < elems; i++){
            this->matrix[i] -= matrix.matrix[i];
        }
    }

    template<unsigned int _columns = columns, unsigned int _rows = rows>
    Matrix<rows, _columns> mult(Matrix<dataType, _columns, _rows>& matrix)const{
        Matrix<rows, _columns> result(false);
        unsigned int line, m_line;

        if(columns != _rows && _columns != rows)
            std::invalid_argument("Matrices informed can't be multiplied!'");
        
        for(unsigned int i = 0; i < rows; i++){
            line = i * rows;
            for(unsigned int j = 0; j < columns; j++){
                m_line = j * rows;
                for(unsigned int k = 0; k < columns; k++){
                    result->matrix[line + k] += transpost.matrix[line + j] * matrix[m_line + i];
                }
            }
        }

        return result;
    }

    MyMatrix& operator*(const dataType& scalar)const{
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

    const float* operator[](unsigned int row)const{
        return M[row * columns];
    }

private:
    std::array<dataType, rows * columns> matrix;
};

#endif