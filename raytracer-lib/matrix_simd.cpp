//
//  matrix.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "matrix_simd.hpp"

#include "tuple.hpp"
#include "tuple_simd.hpp"

using namespace rtlib;

template<typename MatrixType>
MatrixSimd<MatrixType>::MatrixSimd() :
    _matrix(MatrixType())
{
}

template<>
MatrixSimd<simd_double2x2>::MatrixSimd(std::array<std::array<double, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_double2(array[0][0], array[0][1]),
        simd_make_double2(array[1][0], array[1][1]));
}

template<>
MatrixSimd<simd_double3x3>::MatrixSimd(std::array<std::array<double, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_double3(array[0][0], array[0][1], array[0][2]),
        simd_make_double3(array[1][0], array[1][1], array[1][2]),
        simd_make_double3(array[2][0], array[2][1], array[2][2]));
}

template<>
MatrixSimd<simd_double4x4>::MatrixSimd(std::array<std::array<double, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_double4(array[0][0], array[0][1], array[0][2], array[0][3]),
        simd_make_double4(array[1][0], array[1][1], array[1][2], array[1][3]),
        simd_make_double4(array[2][0], array[2][1], array[2][2], array[2][3]),
        simd_make_double4(array[3][0], array[3][1], array[3][2], array[3][3]));
}

template<typename MatrixType>
double MatrixSimd<MatrixType>::at(unsigned int row, unsigned int column) const {
    return _matrix.columns[column][row];
}

template<typename MatrixType>
void MatrixSimd<MatrixType>::set(unsigned int row, unsigned int column, double value) {
    _matrix.columns[column][row] = value;
}

template<typename MatrixType>
double MatrixSimd<MatrixType>::determinant() const {
    return simd_determinant(_matrix);
}

template<typename MatrixType>
MatrixSimd<MatrixType> MatrixSimd<MatrixType>::transpose() const {
    auto matrix = *this;
    matrix._matrix = simd_transpose(matrix._matrix);
    return matrix;
}

template<typename MatrixType>
template<typename ReturnType>
MatrixSimd<ReturnType> MatrixSimd<MatrixType>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<MatrixType> submatrix;
    throw std::logic_error("unimplemented submatrix function");
    return submatrix;
}

template<>
template<>
MatrixSimd<simd_double2x2> MatrixSimd<simd_double2x2>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double2x2> submatrix;
    throw std::logic_error("shouldn't call submatrix on 2x2 matrix");
    return submatrix;
}

template<>
template<>
MatrixSimd<simd_double2x2> MatrixSimd<simd_double3x3>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double2x2> submatrix;

    for (unsigned int row = 0; row < 2; row++) {
        unsigned int adjustRow = row >= removeRow ? row + 1 : row;

        for (unsigned int column = 0; column < 2; column++) {
            unsigned int adjustColumn = column >= removeColumn ? column + 1 : column;

            submatrix.set(row, column, this->_matrix.columns[adjustColumn][adjustRow]);
        }
    }

    return submatrix;
}

template<>
template<>
MatrixSimd<simd_double3x3> MatrixSimd<simd_double4x4>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double3x3> submatrix;

    for (unsigned int row = 0; row < 3; row++) {
        unsigned int adjustRow = row >= removeRow ? row + 1 : row;

        for (unsigned int column = 0; column < 3; column++) {
            unsigned int adjustColumn = column >= removeColumn ? column + 1 : column;

            submatrix.set(row, column, this->_matrix.columns[adjustColumn][adjustRow]);
        }
    }

    return submatrix;
}

template<typename MatrixType>
double MatrixSimd<MatrixType>::minor(unsigned int row, unsigned int column) const {
    throw std::logic_error("unimplemented");
    return 0.0;
}

template<>
double MatrixSimd<simd_double3x3>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_double2x2>(row, column);
    return submatrix.determinant();
}

template<>
double MatrixSimd<simd_double4x4>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_double3x3>(row, column);
    return submatrix.determinant();
}

template<typename MatrixType>
double MatrixSimd<MatrixType>::cofactor(unsigned int row, unsigned int column) const {
    auto minor = this->minor(row, column);
    minor *= ((row + column) % 2) > 0 ? -1 : 1;
    return minor;
}

template<typename MatrixType>
bool MatrixSimd<MatrixType>::invertible() const {
    return determinant() != 0.0;
}

template<typename MatrixType>
MatrixSimd<MatrixType> MatrixSimd<MatrixType>::inverse() const {
    auto matrix = *this;
    matrix._matrix = simd_inverse(matrix._matrix);
    return matrix;
}

template<typename MatrixType>
MatrixSimd<MatrixType>& MatrixSimd<MatrixType>::operator*=(const MatrixSimd<MatrixType>& rhs) {
    this->_matrix = matrix_multiply(this->_matrix, rhs._matrix);
    return *this;
}

template<typename MatrixType>
bool MatrixSimd<MatrixType>::operator==(const MatrixSimd<MatrixType>& rhs) const {
    return simd_almost_equal_elements(this->_matrix, rhs._matrix, 0.00001);
}

template<typename MatrixType>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<MatrixType>& matrix) {
    throw std::logic_error("unimplemented");
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double2x2>& matrix) {
    os << "{{" << std::endl;
    for (unsigned int row = 0; row < 2; row++) {
        os << "{";
        for (unsigned int column = 0; column < 2; column++) {
            os << matrix.at(row, column) << ", ";
        }
        os << "}," << std::endl;
    }
    os << "}}" << std::endl;
    
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double3x3>& matrix) {
    os << "{{" << std::endl;
    for (unsigned int row = 0; row < 3; row++) {
        os << "{";
        for (unsigned int column = 0; column < 3; column++) {
            os << matrix.at(row, column) << ", ";
        }
        os << "}," << std::endl;
    }
    os << "}}" << std::endl;
    
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double4x4>& matrix) {
    os << "{{" << std::endl;
    for (unsigned int row = 0; row < 4; row++) {
        os << "{";
        for (unsigned int column = 0; column < 4; column++) {
            os << matrix.at(row, column) << ", ";
        }
        os << "}," << std::endl;
    }
    os << "}}" << std::endl;
    
    return os;
}

template<typename MatrixType>
MatrixSimd<MatrixType> MatrixSimd<MatrixType>::identityMatrix() {
    MatrixSimd<MatrixType> m;
    throw std::logic_error("no identity matrix for specified matrix type");
    return m;
}

template<>
MatrixSimd<simd_double2x2> MatrixSimd<simd_double2x2>::identityMatrix() {
    MatrixSimd<simd_double2x2> m;
    m._matrix = matrix_identity_double2x2;
    return m;
}

template<>
MatrixSimd<simd_double3x3> MatrixSimd<simd_double3x3>::identityMatrix() {
    MatrixSimd<simd_double3x3> m;
    m._matrix = matrix_identity_double3x3;
    return m;
}

template<>
MatrixSimd<simd_double4x4> MatrixSimd<simd_double4x4>::identityMatrix() {
    MatrixSimd<simd_double4x4> m;
    m._matrix = matrix_identity_double4x4;
    return m;
}

template<typename MatrixType>
MatrixSimd<MatrixType> operator*(const MatrixSimd<MatrixType>& lhs, const MatrixSimd<MatrixType>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template class rtlib::MatrixSimd<simd_double2x2>;
template class rtlib::MatrixSimd<simd_double3x3>;
template class rtlib::MatrixSimd<simd_double4x4>;

template<typename MatrixType>
MatrixSimd<MatrixType> rtlib::operator*(const MatrixSimd<MatrixType>& lhs, const MatrixSimd<MatrixType>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template MatrixSimd<simd_double2x2> rtlib::operator*(const MatrixSimd<simd_double2x2>& lhs, const MatrixSimd<simd_double2x2>& rhs);
template MatrixSimd<simd_double3x3> rtlib::operator*(const MatrixSimd<simd_double3x3>& lhs, const MatrixSimd<simd_double3x3>& rhs);
template MatrixSimd<simd_double4x4> rtlib::operator*(const MatrixSimd<simd_double4x4>& lhs, const MatrixSimd<simd_double4x4>& rhs);

template<typename MatrixType>
TupleSimd rtlib::operator*(const MatrixSimd<MatrixType>& lhs, const TupleSimd& rhs) {
    auto result = TupleSimd();
    throw std::logic_error("unimplemented");
    return result;
}

template<>
TupleSimd rtlib::operator*(const MatrixSimd<simd_double4x4>& lhs, const TupleSimd& rhs) {
    auto result = TupleSimd();
    result._vector = simd_mul(lhs._matrix, rhs._vector);
    return result;
}
