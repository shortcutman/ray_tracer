//
//  intersection.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#include "intersection.hpp"

#include "object.hpp"

using namespace rtlib;

Intersect::Intersect(const Object* obj, double t_) :
object(obj), t(t_) {}

bool Intersect::operator==(const Intersect& rhs) const {
    return this->object == rhs.object && this->t == rhs.t;
}

IntersectValues::IntersectValues(Intersect intersect, Ray ray) :
    intersect(intersect)
{
    point = ray.positionAt(intersect.t);
    vectorToEye = -ray.direction();
    normal = intersect.object->normalAt(point);
    
    if (Tuple::dot(vectorToEye, normal) < 0) {
        inside = true;
        normal = -intersect.object->normalAt(point);
    } else {
        inside = false;
    }
    
    auto epsilonPoint = normal * 0.0000001;
    overPoint = point + epsilonPoint;
}

std::optional<Intersect> rtlib::getFirstHit(Intersections hits) {
    std::optional<Intersect> result;
    
    for (const Intersect& i : hits) {
        if (i.t < 0.0) {
            continue;
        } else if (!result) {
            result = i;
        } else if (result->t > i.t) {
            result = i;
        }
    }
    
    return result;
}
