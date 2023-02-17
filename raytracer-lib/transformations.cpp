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

Matrix4x4 rtlib::translation(double x, double y, double z) {
    auto matrix = Matrix4x4::identityMatrix();
    matrix.set(0, 3, x);
    matrix.set(1, 3, y);
    matrix.set(2, 3, z);
    
    return matrix;
}

Matrix4x4 rtlib::scaling(double x, double y, double z) {
    auto matrix = Matrix4x4::identityMatrix();
    matrix.set(0, 0, x);
    matrix.set(1, 1, y);
    matrix.set(2, 2, z);
    
    return matrix;
}

Matrix4x4 rtlib::rotation_x(double angle) {
    auto matrix = Matrix4x4::identityMatrix();
    
    matrix.set(1, 1, std::cos(angle));
    matrix.set(1, 2, -1.0 * std::sin(angle));
    matrix.set(2, 1, std::sin(angle));
    matrix.set(2, 2, std::cos(angle));
    
    return matrix;
}

Matrix4x4 rtlib::rotation_y(double angle) {
    auto matrix = Matrix4x4::identityMatrix();
    
    matrix.set(0, 0, std::cos(angle));
    matrix.set(0, 2, std::sin(angle));
    matrix.set(2, 0, -1.0 * std::sin(angle));
    matrix.set(2, 2, std::cos(angle));
    
    return matrix;
}

Matrix4x4 rtlib::rotation_z(double angle) {
    auto matrix = Matrix4x4::identityMatrix();
    
    matrix.set(0, 0, std::cos(angle));
    matrix.set(0, 1, -1.0 * std::sin(angle));
    matrix.set(1, 0, std::sin(angle));
    matrix.set(1, 1, std::cos(angle));
    
    return matrix;
}

Matrix4x4 rtlib::shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    auto matrix = Matrix4x4::identityMatrix();
    
    matrix.set(0, 1, xy);
    matrix.set(0, 2, xz);
    matrix.set(1, 0, yx);
    matrix.set(1, 2, yz);
    matrix.set(2, 0, zx);
    matrix.set(2, 1, zy);
    
    return matrix;
}

Matrix4x4 rtlib::viewTransform(const Tuple &from, const Tuple &to, const Tuple &up) {
    auto forwardVector = (to - from).normalised();
    auto leftVector =  rtlib::Tuple::cross(forwardVector, up.normalised());
    auto trueUpVector = rtlib::Tuple::cross(leftVector, forwardVector);
    
    auto orientation = Matrix4x4();
    orientation.set(0, 0, leftVector.x());
    orientation.set(0, 1, leftVector.y());
    orientation.set(0, 2, leftVector.z());
    orientation.set(0, 3, 0.0);
    
    orientation.set(1, 0, trueUpVector.x());
    orientation.set(1, 1, trueUpVector.y());
    orientation.set(1, 2, trueUpVector.z());
    orientation.set(1, 3, 0.0);
    
    orientation.set(2, 0, -forwardVector.x());
    orientation.set(2, 1, -forwardVector.y());
    orientation.set(2, 2, -forwardVector.z());
    orientation.set(2, 3, 0.0);
    
    orientation.set(3, 0, 0.0);
    orientation.set(3, 1, 0.0);
    orientation.set(3, 2, 0.0);
    orientation.set(3, 3, 1.0);
    
    orientation *= rtlib::translation(-from.x(), -from.y(), -from.z());
    
    return orientation;
}
