//
//  tuple.hpp
//  raytracer
//
//  Created by Daniel Burke on 6/2/2023.
//

#ifndef tuple_h
#define tuple_h

#ifdef TUPLE_SIMD

#else

#include "tuple_raw.hpp"

namespace rtlib {

typedef TupleRaw Tuple;

}

#endif

#endif /* tuple_h */
