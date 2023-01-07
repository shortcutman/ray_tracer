//
//  matrix.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "matrix.hpp"

#include "tuple.hpp"

using namespace rtlib;

template<unsigned int N>
Matrix<N>::Matrix()
{
    for (unsigned int row = 0; row < N; row++) {
        _matrix[row].fill(0.0);
    }
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
void Matrix<N>::set(unsigned int row, unsigned int column, double value) {
    _matrix[row][column] = value;
}

template<>
double Matrix<2>::determinant() const {
    return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
}

template<unsigned int N>
double Matrix<N>::determinant() const {
    double det = 0.0;
    
    for (unsigned int i = 0; i < N; i++) {
        det += at(0, i) * cofactor(0, i);
    }
    
    return det;
}

template<unsigned int N>
Matrix<N> Matrix<N>::transpose() const {
    auto matrix = *this;
    
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            matrix._matrix[row][column] = this->_matrix[column][row];
        }
    }

    return matrix;
}

template<unsigned int N>
Matrix<N - 1> Matrix<N>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    Matrix<N-1> submatrix;
    
    for (unsigned int row = 0; row < (N - 1); row++) {
        unsigned int adjustRow = row >= removeRow ? row + 1 : row;
        
        for (unsigned int column = 0; column < (N-1); column++) {
            unsigned int adjustColumn = column >= removeColumn ? column + 1 : column;
            
            submatrix.set(row, column, this->_matrix[adjustRow][adjustColumn]);
        }
    }
    
    return submatrix;
}

template<>
double Matrix<2>::minor(unsigned int row, unsigned int column) const {
    return at(1 - row, 1 - column);
}


template<unsigned int N>
double Matrix<N>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix(row, column);
    return submatrix.determinant();
}

template<unsigned int N>
double Matrix<N>::cofactor(unsigned int row, unsigned int column) const {
    auto minor = this->minor(row, column);
    minor *= (row + column % 2) > 0 ? -1 : 1;
    return minor;
}

template<unsigned int N>
bool Matrix<N>::invertible() const {
    return determinant() != 0.0;
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
Matrix<N> Matrix<N>::identityMatrix() {
    Matrix<N> m;
    
    for (unsigned int diagonalIndex = 0; diagonalIndex < N; diagonalIndex++) {
        m._matrix[diagonalIndex][diagonalIndex] = 1.0;
    }
    
    return m;
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

template<unsigned int N>
Matrix<N> rtlib::operator*(const Matrix<N>& lhs, const Matrix<N>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template Matrix<2> rtlib::operator*(const Matrix<2>& lhs, const Matrix<2>& rhs);
template Matrix<3> rtlib::operator*(const Matrix<3>& lhs, const Matrix<3>& rhs);
template Matrix<4> rtlib::operator*(const Matrix<4>& lhs, const Matrix<4>& rhs);

template<unsigned int N>
Tuple rtlib::operator*(const Matrix<N>& lhs, const Tuple& rhs) {
    auto result = Tuple();
    
    for (unsigned int index = 0; index < N; index++) {
        for (unsigned int size = 0; size < N; size++) {
            result[index] += rhs[size] * lhs.at(index, size);
        }
    }
    
    return result;
}

template Tuple rtlib::operator*(const Matrix<4>& lhs, const Tuple& rhs);
