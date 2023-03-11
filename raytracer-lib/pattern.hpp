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

class Pattern {
private:
    Matrix4x4 _transform;

public:
    Pattern();
    ~Pattern();
    
    void setTransform(Matrix4x4 transform);
    Colour colourAt(const Object* object, Tuple point) const;
    
protected:
    virtual Colour colourAtLocalPoint(Tuple point) const = 0;
};

class StripePattern : public Pattern {
private:
    Colour _colourA;
    Colour _colourB;
    
public:
    StripePattern(Colour colourA, Colour colourB);
    
protected:
    virtual Colour colourAtLocalPoint(Tuple point) const;
};

}


#endif /* pattern_hpp */
