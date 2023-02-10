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
MatrixRaw<N>::MatrixRaw()
{
    for (unsigned int row = 0; row < N; row++) {
        _matrix[row].fill(0.0);
    }
}

template<unsigned int N>
MatrixRaw<N>::MatrixRaw(BaseMatrix matrix) :
    _matrix(matrix)
{
    
}

template<unsigned int N>
double MatrixRaw<N>::at(unsigned int row, unsigned int column) const {
    return _matrix[row][column];
}

template<unsigned int N>
void MatrixRaw<N>::set(unsigned int row, unsigned int column, double value) {
    _matrix[row][column] = value;
}

template<>
double MatrixRaw<2>::determinant() const {
    return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
}

template<unsigned int N>
double MatrixRaw<N>::determinant() const {
    double det = 0.0;
    
    for (unsigned int i = 0; i < N; i++) {
        det += at(0, i) * cofactor(0, i);
    }
    
    return det;
}

template<unsigned int N>
MatrixRaw<N> MatrixRaw<N>::transpose() const {
    auto matrix = *this;
    
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            matrix._matrix[row][column] = this->_matrix[column][row];
        }
    }

    return matrix;
}

template<unsigned int N>
MatrixRaw<N - 1> MatrixRaw<N>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixRaw<N-1> submatrix;
    
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
double MatrixRaw<2>::minor(unsigned int row, unsigned int column) const {
    return at(1 - row, 1 - column);
}


template<unsigned int N>
double MatrixRaw<N>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix(row, column);
    return submatrix.determinant();
}

template<unsigned int N>
double MatrixRaw<N>::cofactor(unsigned int row, unsigned int column) const {
    auto minor = this->minor(row, column);
    minor *= ((row + column) % 2) > 0 ? -1 : 1;
    return minor;
}

template<unsigned int N>
bool MatrixRaw<N>::invertible() const {
    return determinant() != 0.0;
}

template<unsigned int N>
MatrixRaw<N> MatrixRaw<N>::inverse() const {
    MatrixRaw<N> inverse;
    const auto determinant = this->determinant();
    
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            double value = this->cofactor(row, column);
            inverse.set(column, row, value / determinant);
        }
    }
    
    return inverse;
}

template<unsigned int N>
MatrixRaw<N>& MatrixRaw<N>::operator*=(const MatrixRaw<N>& rhs) {
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
bool MatrixRaw<N>::operator==(const MatrixRaw<N>& rhs) const {
    return std::equal(_matrix.begin(), _matrix.end(), rhs._matrix.begin(),
        [] (std::array<double, N> a, std::array<double, N> b) -> bool {
        return std::equal(a.begin(), a.end(), b.begin(), [] (double a, double b) {
            return std::abs(a - b) < 0.00001;
        });
    });
}

template<unsigned int N>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixRaw<N>& matrix) {
    os << "{{" << std::endl;
    for (unsigned int row = 0; row < N; row++) {
        os << "{";
        for (unsigned int column = 0; column < N; column++) {
            os << matrix.at(row, column) << ", ";
        }
        os << "}," << std::endl;
    }
    os << "}}" << std::endl;
    
    return os;
}

template std::ostream& rtlib::operator<<(std::ostream& os, const Matrix<2>& matrix);
template std::ostream& rtlib::operator<<(std::ostream& os, const Matrix<3>& matrix);
template std::ostream& rtlib::operator<<(std::ostream& os, const Matrix<4>& matrix);

template<unsigned int N>
MatrixRaw<N> MatrixRaw<N>::identityMatrix() {
    MatrixRaw<N> m;
    
    for (unsigned int diagonalIndex = 0; diagonalIndex < N; diagonalIndex++) {
        m._matrix[diagonalIndex][diagonalIndex] = 1.0;
    }
    
    return m;
}

template<unsigned int N>
MatrixRaw<N> operator*(const MatrixRaw<N>& lhs, const MatrixRaw<N>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template class rtlib::MatrixRaw<2>;
template class rtlib::MatrixRaw<3>;
template class rtlib::MatrixRaw<4>;

template<unsigned int N>
MatrixRaw<N> rtlib::operator*(const MatrixRaw<N>& lhs, const MatrixRaw<N>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template Matrix<2> rtlib::operator*(const Matrix<2>& lhs, const Matrix<2>& rhs);
template Matrix<3> rtlib::operator*(const Matrix<3>& lhs, const Matrix<3>& rhs);
template Matrix<4> rtlib::operator*(const Matrix<4>& lhs, const Matrix<4>& rhs);

template<unsigned int N>
Tuple rtlib::operator*(const MatrixRaw<N>& lhs, const Tuple& rhs) {
    auto result = Tuple();
    
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            auto value = result[row];
            value += rhs[column] * lhs.at(row, column);
            result.set(row, value);
        }
    }
    
    return result;
}

template Tuple rtlib::operator*(const Matrix<4>& lhs, const Tuple& rhs);
