//
//  PointObject.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 5/3/2023.
//

#include "PointObject.hpp"

using namespace rtlib_tests;

rtlib::Intersections PointObject::intersectsImpl(const rtlib::Ray& ray) const {
    rtlib::Intersections i;
    i.push_back({
        this,
        0.0
    });
    throw std::runtime_error("not implemented");
    return i;
}

rtlib::Tuple PointObject::normalAtImpl(const rtlib::Tuple& point) const {
    throw std::runtime_error("not implemented");
    return rtlib::create_vector(0.0, 0.0, 0.0);
}

