//
//  matrix.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 10/2/2023.
//

#ifndef matrix_h
#define matrix_h

#ifdef MATRIX_SIMD

#include "matrix_simd.hpp"

#else

#include "matrix_raw.hpp"

#endif

#endif /* matrix_h */
