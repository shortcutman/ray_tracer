//
//  ray.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#ifndef ray_hpp
#define ray_hpp

#include "matrix.hpp"
#include "tuple.hpp"

namespace rtlib {

class Ray {
private:
    Tuple _origin;
    Tuple _direction;
    
public:
    Ray();
    Ray(Tuple origin, Tuple direction);
    
    bool valid() const;
    Tuple origin() const;
    Tuple direction() const;
    
    Ray transform(const Matrix4x4& matrix) const;
    Tuple positionAt(double t) const;
};

}

#endif /* ray_hpp */
