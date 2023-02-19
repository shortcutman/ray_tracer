//
//  object.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#include "object.hpp"

#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"

#include <cmath>
#include <numeric>

rtlib::Object::Object() :
    _transform(Matrix4x4::identityMatrix())
{}

rtlib::Matrix4x4 rtlib::Object::transform() const {
    return _transform;
}

void rtlib::Object::setTransform(rtlib::Matrix4x4 matrix) {
    _transform = matrix;
}

rtlib::Material& rtlib::Object::material() {
    return _material;
}

rtlib::Material rtlib::Object::material() const {
    return _material;
}

void rtlib::Object::setMaterial(Material material) {
    _material = material;
}
