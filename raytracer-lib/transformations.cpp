//
//  transformations.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 15/1/2023.
//

#include "transformations.hpp"

#include "matrix.hpp"

#include <cmath>

using namespace rtlib;

Matrix<4> rtlib::translation(double x, double y, double z) {
    auto matrix = Matrix<4>::identityMatrix();
    matrix.set(0, 3, x);
    matrix.set(1, 3, y);
    matrix.set(2, 3, z);
    
    return matrix;
}

Matrix<4> rtlib::scaling(double x, double y, double z) {
    auto matrix = Matrix<4>::identityMatrix();
    matrix.set(0, 0, x);
    matrix.set(1, 1, y);
    matrix.set(2, 2, z);
    
    return matrix;
}

Matrix<4> rtlib::rotation_x(double angle) {
    auto matrix = Matrix<4>::identityMatrix();
    
    matrix.set(1, 1, std::cos(angle));
    matrix.set(1, 2, -1.0 * std::sin(angle));
    matrix.set(2, 1, std::sin(angle));
    matrix.set(2, 2, std::cos(angle));
    
    return matrix;
}

Matrix<4> rtlib::rotation_y(double angle) {
    auto matrix = Matrix<4>::identityMatrix();
    
    matrix.set(0, 0, std::cos(angle));
    matrix.set(0, 2, std::sin(angle));
    matrix.set(2, 0, -1.0 * std::sin(angle));
    matrix.set(2, 2, std::cos(angle));
    
    return matrix;
}

Matrix<4> rtlib::rotation_z(double angle) {
    auto matrix = Matrix<4>::identityMatrix();
    
    matrix.set(0, 0, std::cos(angle));
    matrix.set(0, 1, -1.0 * std::sin(angle));
    matrix.set(1, 0, std::sin(angle));
    matrix.set(1, 1, std::cos(angle));
    
    return matrix;
}

Matrix<4> rtlib::shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    auto matrix = Matrix<4>::identityMatrix();
    
    matrix.set(0, 1, xy);
    matrix.set(0, 2, xz);
    matrix.set(1, 0, yx);
    matrix.set(1, 2, yz);
    matrix.set(2, 0, zx);
    matrix.set(2, 1, zy);
    
    return matrix;
}
