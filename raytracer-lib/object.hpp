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
#include "lighting.hpp"

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
    Matrix4x4 _transform;
    Material _material;
    
public:
    Object();
    ~Object() {}
    
    Matrix4x4 transform() const;
    void setTransform(Matrix4x4 matrix);
    
    Material material() const;
    void setMaterial(Material material);
    
    virtual IntersectHits intersects(const Ray& ray) const = 0;
    virtual Tuple normalAt(const Tuple& point) const = 0;
};

std::optional<Object::Intersect> hit(Object::IntersectHits hits);

class Sphere : public Object {
public:
    Sphere() : Object() {}
    ~Sphere() {}
    
    virtual IntersectHits intersects(const Ray& ray) const;
    virtual Tuple normalAt(const Tuple& point) const;
};

}

#endif /* object_hpp */
