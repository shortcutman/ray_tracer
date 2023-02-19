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
    bool inside;
    
    IntersectValues(Intersect intersect, Ray ray);
};

std::optional<Intersect> getFirstHit(Intersections hits);
    
}
#endif /* intersection_hpp */
