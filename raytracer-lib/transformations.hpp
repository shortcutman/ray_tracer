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
Matrix<4> rotation_x(double angle);
Matrix<4> rotation_y(double angle);
Matrix<4> rotation_z(double angle);
Matrix<4> shearing(double xy, double xz, double yx, double yz, double zx, double zy);

}

#endif /* transformations_hpp */
