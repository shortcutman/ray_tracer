//
//  intersection.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#include "intersection.hpp"

#include "object.hpp"

#include <limits>

using namespace rtlib;

Intersect::Intersect(const Object* obj, double t_) :
object(obj), t(t_) {}

bool Intersect::operator==(const Intersect& rhs) const {
    return this->object == rhs.object && this->t == rhs.t;
}

IntersectValues::IntersectValues(Intersect intersect, Ray ray) :
    intersect(intersect),
    refractiveIndexN1(std::numeric_limits<double>::quiet_NaN()),
    refractiveIndexN2(std::numeric_limits<double>::quiet_NaN())
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
    underPoint = point - epsilonPoint;
    
    reflectionVector = Tuple::reflect(ray.direction(), normal);
}

IntersectValues::IntersectValues(Intersect intersect, Ray ray, const Intersections& intersections) :
IntersectValues(intersect, ray)
{
    auto firstHit = getFirstHit(intersections);
    if (!firstHit) {
        return;
    }
    
    std::vector<const Object*> containers;
    
    for (auto it : intersections) {
        if (it == intersect) {
            if (containers.empty()) {
                refractiveIndexN1 = 1.0;
            } else {
                refractiveIndexN1 = containers.back()->material()._refractiveIndex;
            }
        }
        
        auto existingPos = std::find(containers.begin(), containers.end(), it.object);
        if (existingPos != containers.end()) {
            containers.erase(existingPos);
        } else {
            containers.push_back(it.object);
        }
        
        if (it == intersect) {
            if (containers.empty()) {
                refractiveIndexN2 = 1.0;
            } else {
                refractiveIndexN2 = containers.back()->material()._refractiveIndex;
            }
            
            break;
        }
    }
}

std::optional<Intersect> rtlib::getFirstHit(rtlib::Intersections hits) {
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
