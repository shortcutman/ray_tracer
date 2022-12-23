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
double Matrix<N>::at(unsigned int row, unsigned int column) {
    return _matrix[row][column];
}

template<unsigned int N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    return std::equal(_matrix.begin(), _matrix.end(), rhs._matrix.begin());
}

template class rtlib::Matrix<2>;
template class rtlib::Matrix<3>;
template class rtlib::Matrix<4>;
