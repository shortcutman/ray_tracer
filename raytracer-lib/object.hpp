//
//  object.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#ifndef object_hpp
#define object_hpp

#include <vector>

namespace rtlib {

class Ray;

class Object {
public:
    struct Intersect {
        const Object* object;
        double t;
        
        Intersect(const Object* obj, double t_) :
        object(obj), t(t_) {}
    };
    typedef std::vector<Intersect> IntersectHits;
    
public:
    Object() {}
    ~Object() {}
    
    virtual IntersectHits intersects(const Ray& ray) const = 0;
};

class Sphere : public Object {
public:
    Sphere() : Object() {}
    ~Sphere() {}
    
    virtual IntersectHits intersects(const Ray& ray) const;
};

}

#endif /* object_hpp */
