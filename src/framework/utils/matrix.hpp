#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <array>
#include <stdexcept>

template<typename dataType = float, unsigned int columns = 3, unsigned int rows = 3>
class Matrix{
public:
    typedef Matrix<dataType, columns, rows> MyMatrix;
    typedef Matrix<dataType, rows, columns> MyTranspost;

    Matrix(){
        matrix.fill(0);
    }

    Matrix(std::initializer_list<dataType> list){
        set(list);
    }

    void loadIdentity(){
        matrix.fill(0);
        for(unsigned int i = 0; i < columns; i++){
            matrix[i * columns + i] = 1;
        }
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

    const dataType* get()const{ return matrix.data(); }

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

    template<unsigned int _columns = columns, unsigned int _rows = rows>
    Matrix<dataType, rows, _columns> mult(Matrix<dataType, _columns, _rows>& matrix)const{
        Matrix<dataType, rows, _columns> result;
        unsigned int line;

        if(columns != _rows)
            throw std::invalid_argument("Matrices informed can't be multiplied!'");
        
        for(unsigned int i = 0; i < rows; i++){
            line = i * columns;
            for(unsigned int j = 0; j < _columns; j++){
                for(unsigned int k = 0; k < _columns; k++){
                    result[i][j] += this->matrix[line + k] * matrix[k][j];
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

    const dataType* operator[](unsigned int row)const{
        return matrix.data() + (row * columns);
    }

    dataType* operator[](unsigned int row){
        return matrix.data() + (row * columns);
    }

private:
    std::array<dataType, rows * columns> matrix;
};

#endif