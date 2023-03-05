//
//  pattern.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 5/3/2023.
//

#include "pattern.hpp"

#include <cmath>

using namespace rtlib;

StripePattern::StripePattern(Colour colourA, Colour colourB) :
_colourA(colourA),
_colourB(colourB)
{
}

Colour StripePattern::colourAt(const Object* object, Tuple point) const {
    if (static_cast<int>(std::floor(point.x())) % 2 == 0) {
        return _colourA;
    } else {
        return _colourB;
    }
}
