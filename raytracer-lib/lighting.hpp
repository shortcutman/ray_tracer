//
//  lighting.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 3/2/2023.
//

#ifndef lighting_hpp
#define lighting_hpp

#include "colour.hpp"
#include "material.hpp"
#include "tuple.hpp"

namespace rtlib {

class Light {
private:
    Tuple _position;
    Colour _intensity;
    
public:
    Light(const Tuple& origin, const Colour& intensity);
    
    Tuple origin() const;
    Colour intensity() const;
    
    Colour lightPoint(const Object* object,
                      Tuple point,
                      Tuple vectorToCamera,
                      Tuple normal,
                      bool inShadow) const;
};

}

#endif /* lighting_hpp */
