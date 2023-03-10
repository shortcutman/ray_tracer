//
//  ray.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#include "ray.hpp"

#include "matrix.hpp"

using namespace rtlib;

Ray::Ray()
{
}

Ray::Ray(Tuple origin, Tuple direction) :
    _origin(origin),
    _direction(direction) {
}

bool Ray::valid() const {
    return _origin.isPoint() && _direction.isVector();
}

Tuple Ray::origin() const {
    return _origin;
}

Tuple Ray::direction() const {
    return _direction;
}

Ray Ray::transform(const Matrix4x4& matrix) const {
    auto transformedRay = *this;
    transformedRay._origin = matrix * transformedRay._origin;
    transformedRay._direction = matrix * transformedRay._direction;
    return transformedRay;
}

Tuple Ray::positionAt(double t) const {
    return _origin + _direction * t;
}
