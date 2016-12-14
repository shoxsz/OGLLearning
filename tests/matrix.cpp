#include <iostream>
#include "../src/framework/utils/matrix.hpp"

template<int c, int r>
void printMatrix(Matrix<c, r, int>& matrix){
    for(unsigned int i = 0; i < r; i++){
        for(unsigned int j = 0; j < c; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    Matrix<3, 3, int> matrix({1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<3, 3, int> matrix2({10, 10, 10, 10, 10, 10, 10, 10, 10});
    Matrix<4, 4, int> matrix3;
    Matrix<4, 4, int> matrix4;
    Matrix<4, 4, int> result, result2;

    matrix.sum(matrix2);
    printMatrix<3, 3>(matrix);

    matrix.scale(10);
    printMatrix<3, 3>(matrix);

    matrix2.sub(matrix);
    matrix2.scale(18);
    printMatrix<3, 3>(matrix2);

    matrix3.set({
                    10, 11, 12, 0,
                    31, 32, 33, 0,
                    41, 42, 43, 0,
                    51, 52, 53, 1
    });
    printMatrix<4, 4>(matrix3);

    printMatrix<4, 4>(std::move(matrix3.transpose()));

    matrix4.set({
                    0, 1, 0, 2,
                    1, 4, 2, 8,
                    4, 16, 8, 32,
                    16, 64, 32, 128
    });

    result = std::move(matrix3.mult(matrix4));
    result2 = std::move(matrix4.mult(matrix3));
    printMatrix<4, 4>(result);
    printMatrix<4, 4>(result2);

    result2 *= 0;
    printMatrix<4, 4>(result2);

    try{
        auto no_result = std::move(matrix4.mult<3, 3>(matrix));
    }catch(std::invalid_argument& ex){
        std::cout << "Error: " << ex.what() << std::endl;
    }
}