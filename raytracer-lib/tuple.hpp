//
//  tuple.hpp
//  raytracer
//
//  Created by Daniel Burke on 6/2/2023.
//

#ifndef tuple_h
#define tuple_h

//#define TUPLE_SIMD

#ifdef TUPLE_SIMD

#include "tuple_simd.hpp"

namespace rtlib {

typedef TupleSimd Tuple;

inline Tuple create_point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

inline Tuple create_vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

}

#else

#include "tuple_raw.hpp"

namespace rtlib {

typedef TupleRaw Tuple;

inline Tuple create_point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

inline Tuple create_vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

}

#endif

#endif /* tuple_h */
