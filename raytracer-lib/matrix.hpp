//
//  matrix.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <array>

namespace rtlib {

class Tuple;

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
    
    Matrix<N>& operator*=(const Matrix<N>& rhs);
    
    bool operator==(const Matrix<N>& rhs) const;
};

template<unsigned int N>
Matrix<N> operator*(const Matrix<N>& lhs, const Matrix<N>& rhs);
template<unsigned int N>
Tuple operator*(const Matrix<N>& lhs, const Tuple& rhs);


typedef Matrix<2> Matrix2x2;
typedef Matrix<3> Matrix3x3;
typedef Matrix<4> Matrix4x4;

}

#endif /* matrix_hpp */
