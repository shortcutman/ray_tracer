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
    
    virtual Tuple normalAt(const Tuple& point) const;
    
protected:
    virtual Intersections intersectsImpl(const Ray& ray) const;
};

}


#endif /* sphere_hpp */
