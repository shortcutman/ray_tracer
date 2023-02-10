//
//  matrix.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#ifndef matrix_raw_hpp
#define matrix_raw_hpp

#include "tuple.hpp"

#include <array>
#include <ostream>

namespace rtlib {

template<unsigned int N>
class Matrix {
public:
    typedef std::array<std::array<double, N>, N> BaseMatrix;
    
private:
    BaseMatrix _matrix;
    
public:
    Matrix();
    Matrix(BaseMatrix matrix);
    ~Matrix() {}
    
    double at(unsigned int row, unsigned int column) const;
    void set(unsigned int row, unsigned int column, double value);
    
    double determinant() const;
    Matrix<N> transpose() const;
    Matrix<N - 1> submatrix(unsigned int row, unsigned int column) const;
    double minor(unsigned int row, unsigned int column) const;
    double cofactor(unsigned int row, unsigned int column) const;
    bool invertible() const;
    Matrix<N> inverse() const;
    
    Matrix<N>& operator*=(const Matrix<N>& rhs);
    
    bool operator==(const Matrix<N>& rhs) const;
    
    static Matrix<N> identityMatrix();
};

template<unsigned int N>
std::ostream& operator<< (std::ostream& os, const Matrix<N>& matrix);

template<unsigned int N>
Matrix<N> operator*(const Matrix<N>& lhs, const Matrix<N>& rhs);
template<unsigned int N>
Tuple operator*(const Matrix<N>& lhs, const Tuple& rhs);


typedef Matrix<2> Matrix2x2;
typedef Matrix<3> Matrix3x3;
typedef Matrix<4> Matrix4x4;

}

#endif /* matrix_raw_hpp */
