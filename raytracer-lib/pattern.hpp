//
//  pattern.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 5/3/2023.
//

#ifndef pattern_hpp
#define pattern_hpp

#include "colour.hpp"
#include "matrix.hpp"
#include "tuple.hpp"

namespace rtlib {

class Object;

class StripePattern {
private:
    Colour _colourA;
    Colour _colourB;
    Matrix4x4 _transform;
    
public:
    StripePattern(Colour colourA, Colour colourB);
    
    void setTransform(Matrix4x4 transform);
    Colour colourAt(const Object* object, Tuple point) const;
};

}


#endif /* pattern_hpp */
