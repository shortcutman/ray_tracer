//
//  matrix.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "matrix.hpp"

using namespace rtlib;

template<unsigned int N>
Matrix<N>::Matrix()
{
    
}

template<unsigned int N>
Matrix<N>::Matrix(BaseMatrix matrix) :
    _matrix(matrix)
{
    
}

template<unsigned int N>
double Matrix<N>::at(unsigned int row, unsigned int column) const {
    return _matrix[row][column];
}

template<unsigned int N>
Matrix<N>& Matrix<N>::operator*=(const Matrix<N>& rhs) {
    auto lhs = *this;
    
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            double value = 0.0;
            
            for (unsigned int size = 0; size < N; size++) {
                value += lhs.at(row, size) * rhs.at(size, column);
            }
            
            this->_matrix[row][column] = value;
        }
    }
    
    return *this;
}

template<unsigned int N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    return std::equal(_matrix.begin(), _matrix.end(), rhs._matrix.begin());
}

template<unsigned int N>
Matrix<N> operator*(const Matrix<N>& lhs, const Matrix<N>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template class rtlib::Matrix<2>;
template class rtlib::Matrix<3>;
template class rtlib::Matrix<4>;
