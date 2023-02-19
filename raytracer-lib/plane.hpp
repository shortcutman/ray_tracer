//
//  plane.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#ifndef plane_hpp
#define plane_hpp

#include "object.hpp"

namespace rtlib {

class Plane : public Object {\
public:
    Plane() : Object() {}
    ~Plane() {}
    
protected:
    virtual Intersections intersectsImpl(const Ray& ray) const;
    virtual Tuple normalAtImpl(const Tuple& point) const;
};

}
#endif /* plane_hpp */
