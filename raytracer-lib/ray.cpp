//
//  ray.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#include "ray.hpp"

using namespace rtlib;

Ray::Ray(Tuple origin, Tuple direction) :
    _origin(origin),
    _direction(direction)
{
}

bool Ray::valid() const
{
    return _origin.isPoint() && _direction.isVector();
}

Tuple Ray::origin() const
{
    return _origin;
}

Tuple Ray::direction() const
{
    return _direction;
}
