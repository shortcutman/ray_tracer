//
//  transformations.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 15/1/2023.
//

#include "transformations.hpp"

#include "matrix.hpp"

using namespace rtlib;

Matrix<4> rtlib::translation(double x, double y, double z) {
    auto matrix = Matrix<4>::identityMatrix();
    matrix.set(0, 3, x);
    matrix.set(1, 3, y);
    matrix.set(2, 3, z);
    
    return matrix;
}
