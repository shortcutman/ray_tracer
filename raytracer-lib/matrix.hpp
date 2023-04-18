//
//  matrix.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 10/2/2023.
//

#ifndef matrix_h
#define matrix_h

#define MATRIX_SIMD

#ifdef MATRIX_SIMD

#include "matrix_simd.hpp"

namespace rtlib {
    typedef MatrixSimd2x2Double Matrix2x2;
    typedef MatrixSimd3x3Double Matrix3x3;
    typedef MatrixSimd4x4Double Matrix4x4;
}

#else

#include "matrix_raw.hpp"

namespace rtlib {
    typedef MatrixRaw<2> Matrix2x2;
    typedef MatrixRaw<3> Matrix3x3;
    typedef MatrixRaw<4> Matrix4x4;
}

#endif

#endif /* matrix_h */
