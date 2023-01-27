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

class Ray {
private:
    Tuple _origin;
    Tuple _direction;
    
public:
    Ray(Tuple origin, Tuple direction);
    
    bool valid() const;
    Tuple origin() const;
    Tuple direction() const;
};

}

#endif /* ray_hpp */
