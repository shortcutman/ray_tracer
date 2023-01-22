//
//  transformations.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 15/1/2023.
//

#ifndef transformations_hpp
#define transformations_hpp

namespace rtlib {

template<unsigned int N>
class Matrix;

Matrix<4> translation(double x, double y, double z);
Matrix<4> scaling(double x, double y, double z);

}

#endif /* transformations_hpp */
