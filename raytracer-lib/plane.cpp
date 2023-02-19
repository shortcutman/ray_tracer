//
//  plane.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#include "plane.hpp"

rtlib::Intersections rtlib::Plane::intersectsImpl(const Ray& ray) const {
    if (std::abs(ray.direction().y()) < 0.00001) {
        return Intersections();
    }
    
    auto intersections = Intersections();
    auto t = -ray.origin().y() / ray.direction().y();
    intersections.push_back(Intersect(this, t));
    return intersections;
}

rtlib::Tuple rtlib::Plane::normalAtImpl(const Tuple &point) const {
    return create_vector(0.0, 1.0, 0.0);
}
