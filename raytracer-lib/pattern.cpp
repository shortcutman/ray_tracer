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

Pattern::Pattern() :
_transform(Matrix4x4::identityMatrix())
{
}

Pattern::~Pattern()
{
}

void Pattern::setTransform(Matrix4x4 transform) {
    _transform = transform;
}

Colour Pattern::colourAt(const Object* object, Tuple point) const {
    auto transformedPoint = object->transform().inverse() * point;
    transformedPoint = _transform.inverse() * transformedPoint;
    return colourAtLocalPoint(transformedPoint);
}

StripePattern::StripePattern(Colour colourA, Colour colourB) :
_colourA(colourA),
_colourB(colourB)
{
}

Colour StripePattern::colourAtLocalPoint(Tuple point) const {
    if (static_cast<int>(std::floor(point.x())) % 2 == 0) {
        return _colourA;
    } else {
        return _colourB;
    }
}

GradientPattern::GradientPattern(Colour colourA, Colour colourB) :
_colourA(colourA),
_colourB(colourB)
{
}

Colour GradientPattern::colourAtLocalPoint(Tuple point) const {
    auto distance = _colourB - _colourA;
    auto fraction = point.x() - std::floor(point.x());
    auto result = _colourA + distance * fraction;
    return result;
}
