//
//  intersection.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#ifndef intersection_hpp
#define intersection_hpp

#include "ray.hpp"
#include "tuple.hpp"

#include <vector>
#include <optional>

namespace rtlib {

class Object;

struct Intersect {
    const Object* object;
    double t;
    
    Intersect(const Object* obj, double t_);
    bool operator==(const Intersect& rhs) const;
};
typedef std::vector<Intersect> Intersections;

struct IntersectValues {
    Intersect intersect;
    Tuple point;
    Tuple vectorToEye;
    Tuple normal;
    Tuple overPoint;
    Tuple underPoint;
    Tuple reflectionVector;
    bool inside;
    double refractiveIndexN1; //material being exited
    double refractiveIndexN2; //material being entered
    
    
    IntersectValues(Intersect intersect, Ray ray);
    IntersectValues(Intersect intersect, Ray ray, const Intersections& intersections);
};

std::optional<Intersect> getFirstHit(Intersections hits);

double schlickReflectance(const IntersectValues& values);
    
}
#endif /* intersection_hpp */
