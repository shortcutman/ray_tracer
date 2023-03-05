//
//  material.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 5/3/2023.
//

#include "material.hpp"

using namespace rtlib;

Colour Material::colourAt(const Object* object, Tuple point) const {
    if (_pattern) {
        return _pattern->colourAt(object, point);
    } else {
        return _colour;
    }
}
