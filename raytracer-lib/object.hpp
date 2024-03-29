//
//  object.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#ifndef object_hpp
#define object_hpp

#include "intersection.hpp"
#include "lighting.hpp"
#include "matrix.hpp"

namespace rtlib {

class Ray;

class Object {
private:
    Matrix4x4 _transform;
    Material _material;
    
public:
    Object();
    virtual ~Object() {}
    
    Matrix4x4 transform() const;
    void setTransform(Matrix4x4 matrix);
    
    Material& material();
    Material material() const;
    void setMaterial(Material material);
    
    Intersections intersects(const Ray& ray) const;
    Tuple normalAt(const Tuple& point) const;
    
protected:
    virtual Intersections intersectsImpl(const Ray& ray) const = 0;
    virtual Tuple normalAtImpl(const Tuple& point) const = 0;
};

}

#endif /* object_hpp */
