//
//  pattern.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 5/3/2023.
//

#include "pattern.hpp"

#include "object.hpp"

#include <cmath>

using namespace rtlib;

StripePattern::StripePattern(Colour colourA, Colour colourB) :
_transform(Matrix4x4::identityMatrix()),
_colourA(colourA),
_colourB(colourB)
{
}

void StripePattern::setTransform(Matrix4x4 transform) {
    _transform = transform;
}

Colour StripePattern::colourAt(const Object* object, Tuple point) const {
    auto transformedPoint = object->transform().inverse() * point;
    transformedPoint = _transform.inverse() * transformedPoint;
    
    if (static_cast<int>(std::floor(transformedPoint.x())) % 2 == 0) {
        return _colourA;
    } else {
        return _colourB;
    }
}
