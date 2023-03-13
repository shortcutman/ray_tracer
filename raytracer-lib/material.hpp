//
//  material.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 5/3/2023.
//

#ifndef material_hpp
#define material_hpp

#include "colour.hpp"
#include "pattern.hpp"

#include <memory>
#include <optional>

namespace rtlib {

class Object;

class Material {
public:
    std::shared_ptr<Pattern> _pattern;
    Colour _colour = Colour(1.0, 1.0, 1.0);
    double _ambient = 0.1;
    double _diffuse = 0.9;
    double _specular = 0.9;
    double _shininess = 200.0;
    double _reflective = 0.0;
    double _transparency = 0.0;
    double _refractiveIndex = 1.0;
    
public:
    Colour colourAt(const Object* object, Tuple point) const;
};

}
#endif /* material_hpp */
