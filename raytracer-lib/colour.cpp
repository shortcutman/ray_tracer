//
//  colour.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "colour.hpp"

using namespace rtlib;

Colour::Colour() :
    TupleRaw()
{
}

Colour::Colour(double red, double green, double blue) :
    TupleRaw(red, green, blue)
{
}

Colour::Colour(const TupleRaw& t) :
    TupleRaw(t)
{
}

double Colour::red() const {
    return x();
}

double Colour::green() const {
    return y();
}

double Colour::blue() const {
    return z();
}

Colour& Colour::operator*=(const Colour& rhs) {
    this->_x *= rhs.x();
    this->_y *= rhs.y();
    this->_z *= rhs.z();
    return *this;
}

Colour rtlib::operator*(Colour lhs, const Colour& rhs) {
    lhs *= rhs;
    return lhs;
}

