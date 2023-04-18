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

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType>::MatrixSimd() :
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

template<>
MatrixSimd<simd_float2x2, float>::MatrixSimd(std::array<std::array<float, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_float2(array[0][0], array[0][1]),
        simd_make_float2(array[1][0], array[1][1]));
}

template<>
MatrixSimd<simd_float3x3, float>::MatrixSimd(std::array<std::array<float, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_float3(array[0][0], array[0][1], array[0][2]),
        simd_make_float3(array[1][0], array[1][1], array[1][2]),
        simd_make_float3(array[2][0], array[2][1], array[2][2]));
}

template<>
MatrixSimd<simd_float4x4, float>::MatrixSimd(std::array<std::array<float, 4>, 4> array)
{
    _matrix = simd_matrix_from_rows(
        simd_make_float4(array[0][0], array[0][1], array[0][2], array[0][3]),
        simd_make_float4(array[1][0], array[1][1], array[1][2], array[1][3]),
        simd_make_float4(array[2][0], array[2][1], array[2][2], array[2][3]),
        simd_make_float4(array[3][0], array[3][1], array[3][2], array[3][3]));
}

template<typename MatrixType, typename FloatType>
FloatType MatrixSimd<MatrixType, FloatType>::at(unsigned int row, unsigned int column) const {
    return _matrix.columns[column][row];
}

template<typename MatrixType, typename FloatType>
void MatrixSimd<MatrixType, FloatType>::set(unsigned int row, unsigned int column, FloatType value) {
    _matrix.columns[column][row] = value;
}

template<typename MatrixType, typename FloatType>
FloatType MatrixSimd<MatrixType, FloatType>::determinant() const {
    return simd_determinant(_matrix);
}

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> MatrixSimd<MatrixType, FloatType>::transpose() const {
    auto matrix = *this;
    matrix._matrix = simd_transpose(matrix._matrix);
    return matrix;
}

template<typename MatrixType, typename FloatType>
template<typename ReturnSimdType, typename ReturnFloatType>
MatrixSimd<ReturnSimdType, ReturnFloatType> MatrixSimd<MatrixType, FloatType>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<MatrixType> submatrix;
    throw std::logic_error("unimplemented submatrix function");
    return submatrix;
}

template<>
template<>
MatrixSimd<simd_double2x2, double> MatrixSimd<simd_double2x2, double>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double2x2, double> submatrix;
    throw std::logic_error("shouldn't call submatrix on 2x2 matrix");
    return submatrix;
}

template<>
template<>
MatrixSimd<simd_double2x2, double> MatrixSimd<simd_double3x3, double>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double2x2, double> submatrix;

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
MatrixSimd<simd_double3x3, double> MatrixSimd<simd_double4x4, double>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_double3x3, double> submatrix;

    for (unsigned int row = 0; row < 3; row++) {
        unsigned int adjustRow = row >= removeRow ? row + 1 : row;

        for (unsigned int column = 0; column < 3; column++) {
            unsigned int adjustColumn = column >= removeColumn ? column + 1 : column;

            submatrix.set(row, column, this->_matrix.columns[adjustColumn][adjustRow]);
        }
    }

    return submatrix;
}

template<>
template<>
MatrixSimd<simd_float2x2, float> MatrixSimd<simd_float2x2, float>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_float2x2, float> submatrix;
    throw std::logic_error("shouldn't call submatrix on 2x2 matrix");
    return submatrix;
}

template<>
template<>
MatrixSimd<simd_float2x2, float> MatrixSimd<simd_float3x3, float>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_float2x2, float> submatrix;

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
MatrixSimd<simd_float3x3, float> MatrixSimd<simd_float4x4, float>::submatrix(unsigned int removeRow, unsigned int removeColumn) const {
    MatrixSimd<simd_float3x3, float> submatrix;

    for (unsigned int row = 0; row < 3; row++) {
        unsigned int adjustRow = row >= removeRow ? row + 1 : row;

        for (unsigned int column = 0; column < 3; column++) {
            unsigned int adjustColumn = column >= removeColumn ? column + 1 : column;

            submatrix.set(row, column, this->_matrix.columns[adjustColumn][adjustRow]);
        }
    }

    return submatrix;
}

template<typename MatrixType, typename FloatType>
FloatType MatrixSimd<MatrixType, FloatType>::minor(unsigned int row, unsigned int column) const {
    throw std::logic_error("unimplemented");
    return 0.0;
}

template<>
double MatrixSimd<simd_double3x3, double>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_double2x2, double>(row, column);
    return submatrix.determinant();
}

template<>
double MatrixSimd<simd_double4x4, double>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_double3x3, double>(row, column);
    return submatrix.determinant();
}

template<>
float MatrixSimd<simd_float3x3, float>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_float2x2, float>(row, column);
    return submatrix.determinant();
}

template<>
float MatrixSimd<simd_float4x4, float>::minor(unsigned int row, unsigned int column) const {
    auto submatrix = this->submatrix<simd_float3x3, float>(row, column);
    return submatrix.determinant();
}

template<typename MatrixType, typename FloatType>
FloatType MatrixSimd<MatrixType, FloatType>::cofactor(unsigned int row, unsigned int column) const {
    auto minor = this->minor(row, column);
    minor *= ((row + column) % 2) > 0 ? -1 : 1;
    return minor;
}

template<typename MatrixType, typename FloatType>
bool MatrixSimd<MatrixType, FloatType>::invertible() const {
    return determinant() != 0.0;
}

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> MatrixSimd<MatrixType, FloatType>::inverse() const {
    auto matrix = *this;
    matrix._matrix = simd_inverse(matrix._matrix);
    return matrix;
}

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType>& MatrixSimd<MatrixType, FloatType>::operator*=(const MatrixSimd<MatrixType, FloatType>& rhs) {
    this->_matrix = matrix_multiply(this->_matrix, rhs._matrix);
    return *this;
}

template<typename MatrixType, typename FloatType>
bool MatrixSimd<MatrixType, FloatType>::operator==(const MatrixSimd<MatrixType, FloatType>& rhs) const {
    return simd_almost_equal_elements(this->_matrix, rhs._matrix, 0.00001);
}

template<typename MatrixType, typename MatrixFloatType>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<MatrixType, MatrixFloatType>& matrix) {
    throw std::logic_error("unimplemented");
    return os;
}

namespace {

template<typename MatrixType, typename FloatType, int Count>
void print(std::ostream& os, const MatrixSimd<MatrixType, FloatType>& matrix) {
    os << "{{" << std::endl;
    for (unsigned int row = 0; row < Count; row++) {
        os << "{";
        for (unsigned int column = 0; column < Count; column++) {
            os << matrix.at(row, column) << ", ";
        }
        os << "}," << std::endl;
    }
    os << "}}" << std::endl;
}

}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double2x2, double>& matrix) {
    print<simd_double2x2, double, 2>(os, matrix);
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double3x3, double>& matrix) {
    print<simd_double3x3, double, 3>(os, matrix);
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_double4x4, double>& matrix) {
    print<simd_double4x4, double, 4>(os, matrix);
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_float2x2, float>& matrix) {
    print<simd_float2x2, float, 2>(os, matrix);
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_float3x3, float>& matrix) {
    print<simd_float3x3, float, 3>(os, matrix);
    return os;
}

template<>
std::ostream& rtlib::operator<<(std::ostream& os, const MatrixSimd<simd_float4x4, float>& matrix) {
    print<simd_float4x4, float, 4>(os, matrix);
    return os;
}

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> MatrixSimd<MatrixType, FloatType>::identityMatrix() {
    MatrixSimd<MatrixType, FloatType> m;
    throw std::logic_error("no identity matrix for specified matrix type");
    return m;
}

template<>
MatrixSimd<simd_double2x2, double> MatrixSimd<simd_double2x2, double>::identityMatrix() {
    MatrixSimd<simd_double2x2, double> m;
    m._matrix = matrix_identity_double2x2;
    return m;
}

template<>
MatrixSimd<simd_double3x3, double> MatrixSimd<simd_double3x3, double>::identityMatrix() {
    MatrixSimd<simd_double3x3, double> m;
    m._matrix = matrix_identity_double3x3;
    return m;
}

template<>
MatrixSimd<simd_double4x4, double> MatrixSimd<simd_double4x4, double>::identityMatrix() {
    MatrixSimd<simd_double4x4, double> m;
    m._matrix = matrix_identity_double4x4;
    return m;
}

template<>
MatrixSimd<simd_float2x2, float> MatrixSimd<simd_float2x2, float>::identityMatrix() {
    MatrixSimd<simd_float2x2, float> m;
    m._matrix = matrix_identity_float2x2;
    return m;
}

template<>
MatrixSimd<simd_float3x3, float> MatrixSimd<simd_float3x3, float>::identityMatrix() {
    MatrixSimd<simd_float3x3, float> m;
    m._matrix = matrix_identity_float3x3;
    return m;
}

template<>
MatrixSimd<simd_float4x4, float> MatrixSimd<simd_float4x4, float>::identityMatrix() {
    MatrixSimd<simd_float4x4, float> m;
    m._matrix = matrix_identity_float4x4;
    return m;
}

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> operator*(const MatrixSimd<MatrixType, FloatType>& lhs, const MatrixSimd<MatrixType, FloatType>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template class rtlib::MatrixSimd<simd_double2x2, double>;
template class rtlib::MatrixSimd<simd_double3x3, double>;
template class rtlib::MatrixSimd<simd_double4x4, double>;

template class rtlib::MatrixSimd<simd_float2x2, float>;
template class rtlib::MatrixSimd<simd_float3x3, float>;
template class rtlib::MatrixSimd<simd_float4x4, float>;

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> rtlib::operator*(const MatrixSimd<MatrixType, FloatType>& lhs, const MatrixSimd<MatrixType, FloatType>& rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

template MatrixSimd<simd_double2x2, double> rtlib::operator*(const MatrixSimd<simd_double2x2, double>& lhs, const MatrixSimd<simd_double2x2, double>& rhs);
template MatrixSimd<simd_double3x3, double> rtlib::operator*(const MatrixSimd<simd_double3x3, double>& lhs, const MatrixSimd<simd_double3x3, double>& rhs);
template MatrixSimd<simd_double4x4, double> rtlib::operator*(const MatrixSimd<simd_double4x4, double>& lhs, const MatrixSimd<simd_double4x4, double>& rhs);

template MatrixSimd<simd_float2x2, float> rtlib::operator*(const MatrixSimd<simd_float2x2, float>& lhs, const MatrixSimd<simd_float2x2, float>& rhs);
template MatrixSimd<simd_float3x3, float> rtlib::operator*(const MatrixSimd<simd_float3x3, float>& lhs, const MatrixSimd<simd_float3x3, float>& rhs);
template MatrixSimd<simd_float4x4, float> rtlib::operator*(const MatrixSimd<simd_float4x4, float>& lhs, const MatrixSimd<simd_float4x4, float>& rhs);


template<typename MatrixType, typename FloatType>
TupleSimd rtlib::operator*(const MatrixSimd<MatrixType, FloatType>& lhs, const TupleSimd& rhs) {
    auto result = TupleSimd();
    throw std::logic_error("unimplemented");
    return result;
}

template<>
TupleSimd rtlib::operator*(const MatrixSimd<simd_double4x4, double>& lhs, const TupleSimd& rhs) {
    auto result = TupleSimd();
    result._vector = simd_mul(lhs._matrix, rhs._vector);
    return result;
}

template<>
TupleSimd rtlib::operator*(const MatrixSimd<simd_float4x4, float>& lhs, const TupleSimd& rhs) {
    auto result = TupleSimd();
    simd_float4 cast = simd_float(rhs._vector);
    result._vector = simd_double(simd_mul(lhs._matrix, cast));
    return result;
}
