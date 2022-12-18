//
//  tuple.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "tuple.hpp"

using namespace rtlib;

Tuple::Tuple() :
    _x(0.0f),
    _y(0.0f),
    _z(0.0f),
    _w(0.0f) {
}

Tuple::Tuple(float x, float y, float z) :
    _x(x),
    _y(y),
    _z(z),
    _w(0.0f) {
}

Tuple::Tuple(float x, float y, float z, float w) :
    _x(x),
    _y(y),
    _z(z),
    _w(w) {
}

float Tuple::x() const {
    return _x;
}

float Tuple::y() const {
    return _y;
}

float Tuple::z() const {
    return _z;
}

float Tuple::w() const {
    return _w;
}

bool Tuple::isPoint() const {
    return _w == 1.0f;
}

bool Tuple::isVector() const {
    return _w != 1.0f;
}

Tuple rtlib::create_point(float x, float y, float z) {
    return Tuple(x, y, z, 1.0f);
}

Tuple rtlib::create_vector(float x, float y, float z) {
    return Tuple(x, y, z, 0.0f);
}
