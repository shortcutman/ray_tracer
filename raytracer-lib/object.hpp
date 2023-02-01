//
//  object.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#ifndef object_hpp
#define object_hpp

#include <vector>
#include <optional>

#include "matrix.hpp"

namespace rtlib {

class Ray;

class Object {
public:
    struct Intersect {
        const Object* object;
        double t;
        
        Intersect(const Object* obj, double t_);
        bool operator==(const Intersect& rhs) const;
    };
    typedef std::vector<Intersect> IntersectHits;
    
private:
    Matrix<4> _transform;
    
public:
    Object();
    ~Object() {}
    
    Matrix<4> transform() const;
    void setTransform(Matrix<4> matrix);
    
    virtual IntersectHits intersects(const Ray& ray) const = 0;
};

std::optional<Object::Intersect> hit(Object::IntersectHits hits);

class Sphere : public Object {
public:
    Sphere() : Object() {}
    ~Sphere() {}
    
    virtual IntersectHits intersects(const Ray& ray) const;
};

}

#endif /* object_hpp */
