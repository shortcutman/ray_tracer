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

template<typename MatrixType>
class MatrixSimd {
public:
    typedef MatrixType BaseMatrix;
    typedef std::array<std::array<double, 2>, 2> Raw2x2;
    typedef std::array<std::array<double, 3>, 3> Raw3x3;
    typedef std::array<std::array<double, 4>, 4> Raw4x4;


private:
    BaseMatrix _matrix;
    
public:
    MatrixSimd();
    MatrixSimd(std::array<std::array<double, 4>, 4> matrix);
    
    ~MatrixSimd() {}
    
    double at(unsigned int row, unsigned int column) const;
    void set(unsigned int row, unsigned int column, double value);
    
    double determinant() const;
    MatrixSimd<MatrixType> transpose() const;
    double minor(unsigned int row, unsigned int column) const;
    double cofactor(unsigned int row, unsigned int column) const;
    bool invertible() const;
    MatrixSimd<MatrixType> inverse() const;
    
    MatrixSimd<MatrixType>& operator*=(const MatrixSimd<MatrixType>& rhs);
    
    bool operator==(const MatrixSimd<MatrixType>& rhs) const;
    
    template<typename ReturnType>
    MatrixSimd<ReturnType> submatrix(unsigned int row, unsigned int column) const;
    
    static MatrixSimd<MatrixType> identityMatrix();
    
};

template<typename MatrixType>
std::ostream& operator<< (std::ostream& os, const MatrixSimd<MatrixType>& matrix);

template<typename MatrixType>
MatrixSimd<MatrixType> operator*(const MatrixSimd<MatrixType>& lhs, const MatrixSimd<MatrixType>& rhs);
template<typename MatrixType>
Tuple operator*(const MatrixSimd<MatrixType>& lhs, const Tuple& rhs);

typedef MatrixSimd<simd_double2x2> MatrixSimd2x2;
typedef MatrixSimd<simd_double3x3> MatrixSimd3x3;
typedef MatrixSimd<simd_double4x4> MatrixSimd4x4;

}

#endif /* matrix_simd_hpp */
