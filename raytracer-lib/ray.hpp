//
//  ray.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#ifndef ray_hpp
#define ray_hpp

#include "tuple.hpp"

namespace rtlib {

template<unsigned int N>
class Matrix;

class Ray {
private:
    Tuple _origin;
    Tuple _direction;
    
public:
    Ray(Tuple origin, Tuple direction);
    
    bool valid() const;
    Tuple origin() const;
    Tuple direction() const;
    
    Ray transform(const Matrix<4>& matrix) const;
    Tuple positionAt(double t) const;
};

}

#endif /* ray_hpp */
