//
//  lighting.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 3/2/2023.
//

#ifndef lighting_hpp
#define lighting_hpp

#include "colour.hpp"
#include "tuple.hpp"

namespace rtlib {

class Material;

class Light {
private:
    Tuple _position;
    Colour _intensity;
    
public:
    Light(const Tuple& origin, const Colour& intensity);
    
    Tuple origin() const;
    Colour intensity() const;
    
    Colour lightPoint(Material material,
                      Tuple point,
                      Tuple camera,
                      Tuple normal) const;
};

class Material {
public:
    Colour _colour = Colour(1.0, 1.0, 1.0);
    double _ambient = 0.1;
    double _diffuse = 0.9;
    double _specular = 0.9;
    double _shininess = 200.0;
};

}

#endif /* lighting_hpp */
