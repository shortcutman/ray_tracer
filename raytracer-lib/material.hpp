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

#include <optional>

namespace rtlib {

class Material {
public:
    std::optional<StripePattern> _pattern;
    Colour _colour = Colour(1.0, 1.0, 1.0);
    double _ambient = 0.1;
    double _diffuse = 0.9;
    double _specular = 0.9;
    double _shininess = 200.0;
    
public:
    Colour colourAt(Tuple point) const;
};

}
#endif /* material_hpp */
