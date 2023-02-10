//
//  transformations.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 15/1/2023.
//

#ifndef transformations_hpp
#define transformations_hpp

#include "matrix.hpp"

namespace rtlib {

Matrix4x4 translation(double x, double y, double z);
Matrix4x4 scaling(double x, double y, double z);
Matrix4x4 rotation_x(double angle);
Matrix4x4 rotation_y(double angle);
Matrix4x4 rotation_z(double angle);
Matrix4x4 shearing(double xy, double xz, double yx, double yz, double zx, double zy);

}

#endif /* transformations_hpp */
