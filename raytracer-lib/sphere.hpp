//
//  sphere.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#ifndef sphere_hpp
#define sphere_hpp


#include "object.hpp"

namespace rtlib {

class Sphere : public Object {
public:
    Sphere() : Object() {}
    ~Sphere() {}
    
    virtual Intersections intersects(const Ray& ray) const;
    virtual Tuple normalAt(const Tuple& point) const;
};

}


#endif /* sphere_hpp */
