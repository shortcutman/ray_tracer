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
class MatrixRaw {
public:
    typedef std::array<std::array<double, N>, N> BaseMatrix;
    
private:
    BaseMatrix _matrix;
    
public:
    MatrixRaw();
    MatrixRaw(BaseMatrix matrix);
    ~MatrixRaw() {}
    
    double at(unsigned int row, unsigned int column) const;
    void set(unsigned int row, unsigned int column, double value);
    
    double determinant() const;
    MatrixRaw<N> transpose() const;
    MatrixRaw<N - 1> submatrix(unsigned int row, unsigned int column) const;
    double minor(unsigned int row, unsigned int column) const;
    double cofactor(unsigned int row, unsigned int column) const;
    bool invertible() const;
    MatrixRaw<N> inverse() const;
    
    MatrixRaw<N>& operator*=(const MatrixRaw<N>& rhs);
    
    bool operator==(const MatrixRaw<N>& rhs) const;
    
    static MatrixRaw<N> identityMatrix();
};

template<unsigned int N>
std::ostream& operator<< (std::ostream& os, const MatrixRaw<N>& matrix);

template<unsigned int N>
MatrixRaw<N> operator*(const MatrixRaw<N>& lhs, const MatrixRaw<N>& rhs);
template<unsigned int N>
Tuple operator*(const MatrixRaw<N>& lhs, const Tuple& rhs);


typedef MatrixRaw<2> MatrixRaw2x2;
typedef MatrixRaw<3> MatrixRaw3x3;
typedef MatrixRaw<4> MatrixRaw4x4;

}

#endif /* matrix_raw_hpp */
