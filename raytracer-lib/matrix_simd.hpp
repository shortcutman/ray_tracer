//
//  matrix.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#ifndef matrix_simd_hpp
#define matrix_simd_hpp

#include "tuple.hpp"

#include <array>
#include <ostream>
#include <simd/simd.h>

namespace rtlib {

class TupleSimd;

template<typename MatrixType, typename FloatType = double>
class MatrixSimd {
public:
    typedef MatrixType BaseMatrix;

private:
    BaseMatrix _matrix;
    
public:
    MatrixSimd();
    MatrixSimd(std::array<std::array<FloatType, 4>, 4> matrix);
    
    ~MatrixSimd() {}
    
    FloatType at(unsigned int row, unsigned int column) const;
    void set(unsigned int row, unsigned int column, FloatType value);
    
    FloatType determinant() const;
    MatrixSimd<MatrixType, FloatType> transpose() const;
    FloatType minor(unsigned int row, unsigned int column) const;
    FloatType cofactor(unsigned int row, unsigned int column) const;
    bool invertible() const;
    MatrixSimd<MatrixType, FloatType> inverse() const;
    
    MatrixSimd<MatrixType, FloatType>& operator*=(const MatrixSimd<MatrixType, FloatType>& rhs);
    
    bool operator==(const MatrixSimd<MatrixType, FloatType>& rhs) const;
    
    template<typename ReturnSimdType, typename ReturnFloatType>
    MatrixSimd<ReturnSimdType, ReturnFloatType> submatrix(unsigned int row, unsigned int column) const;
    
    template<typename MultiplyMatrix, typename MultiplyFloat>
    friend TupleSimd operator*(const MatrixSimd<MultiplyMatrix, MultiplyFloat>& lhs, const TupleSimd& rhs);
    
    static MatrixSimd<MatrixType, FloatType> identityMatrix();
    
};

template<typename MatrixType, typename MatrixFloatType>
std::ostream& operator<< (std::ostream& os, const MatrixSimd<MatrixType, MatrixFloatType>& matrix);

template<typename MatrixType, typename FloatType>
MatrixSimd<MatrixType, FloatType> operator*(const MatrixSimd<MatrixType, FloatType>& lhs, const MatrixSimd<MatrixType, FloatType>& rhs);

template<typename MatrixType, typename FloatType>
TupleSimd operator*(const MatrixSimd<MatrixType, FloatType>& lhs, const TupleSimd& rhs);

typedef MatrixSimd<simd_double2x2, double> MatrixSimd2x2Double;
typedef MatrixSimd<simd_double3x3, double> MatrixSimd3x3Double;
typedef MatrixSimd<simd_double4x4, double> MatrixSimd4x4Double;

typedef MatrixSimd<simd_float2x2, float> MatrixSimd2x2Float;
typedef MatrixSimd<simd_float3x3, float> MatrixSimd3x3Float;
typedef MatrixSimd<simd_float4x4, float> MatrixSimd4x4Float;

}

#endif /* matrix_simd_hpp */
