//
//  colour.hpp
//  raytracer
//
//  Created by Daniel Burke on 23/12/2022.
//

#ifndef colour_h
#define colour_h

#include "tuple_raw.hpp"

namespace rtlib {

class Colour : public TupleRaw {
public:
    Colour();
    Colour(double red, double green, double blue);
    Colour(const TupleRaw& t);
    ~Colour() {}
    
    double red() const;
    double green() const;
    double blue() const;
    
    Colour& operator*=(const Colour& rhs);
};

Colour operator*(Colour lhs, const Colour& rhs);

}


#endif /* colour_h */
