//
//  tuple.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "tuple_raw.hpp"

#include <cmath>
#include <stdexcept>

using namespace rtlib;

TupleRaw::TupleRaw() :
    _x(0.0),
    _y(0.0),
    _z(0.0),
    _w(0.0) {
}

TupleRaw::TupleRaw(double x, double y, double z) :
    _x(x),
    _y(y),
    _z(z),
    _w(0.0) {
}

TupleRaw::TupleRaw(double x, double y, double z, double w) :
    _x(x),
    _y(y),
    _z(z),
    _w(w) {
}

double TupleRaw::x() const {
    return _x;
}

double TupleRaw::y() const {
    return _y;
}

double TupleRaw::z() const {
    return _z;
}

double TupleRaw::w() const {
    return _w;
}

void TupleRaw::setX(double x) {
    _x = x;
}

void TupleRaw::setY(double y) {
    _y = y;
}

void TupleRaw::setZ(double z) {
    _z = z;
}

void TupleRaw::setW(double w) {
    _w = w;
}

double TupleRaw::operator[](size_t index) const {
    switch (index) {
        case 0:
            return _x;
            
        case 1:
            return _y;
            
        case 2:
            return _z;
            
        case 3:
            return _w;
    }
    
    throw std::runtime_error("index out of range");
    return 0.0;
}

void TupleRaw::set(size_t index, double value) {
    switch (index) {
        case 0:
            _x = value;
            return;
            
        case 1:
            _y = value;
            return;
            
        case 2:
            _z = value;
            return;
            
        case 3:
            _w = value;
            return;
    }
    
    throw std::runtime_error("index out of range");
}


double TupleRaw::magnitude() const {
    return std::sqrt(std::pow(_x, 2) +
                     std::pow(_y, 2) +
                     std::pow(_z, 2) +
                     std::pow(_w, 2));
}

bool TupleRaw::isPoint() const {
    return _w == 1.0;
}

bool TupleRaw::isVector() const {
    return _w == 0.0;
}

TupleRaw& TupleRaw::operator+=(const TupleRaw& rhs) {
    this->_x += rhs.x();
    this->_y += rhs.y();
    this->_z += rhs.z();
    this->_w += rhs.w();
    return *this;
}

TupleRaw& TupleRaw::operator-=(const TupleRaw& rhs) {
    this->_x -= rhs.x();
    this->_y -= rhs.y();
    this->_z -= rhs.z();
    this->_w -= rhs.w();
    return *this;
}

TupleRaw& TupleRaw::operator*=(double rhs) {
    this->_x *= rhs;
    this->_y *= rhs;
    this->_z *= rhs;
    this->_w *= rhs;
    return *this;
}

TupleRaw& TupleRaw::operator/=(double rhs) {
    this->_x /= rhs;
    this->_y /= rhs;
    this->_z /= rhs;
    this->_w /= rhs;
    return *this;
}

TupleRaw TupleRaw::operator-() {
    auto t = *this;
    t._x *= -1.0;
    t._y *= -1.0;
    t._z *= -1.0;
    t._w *= -1.0;
    return t;
}

TupleRaw TupleRaw::normalised() const {
    auto t = *this;
    auto magnitude = this->magnitude();
    t._x /= magnitude;
    t._y /= magnitude;
    t._z /= magnitude;
    t._w /= magnitude;
    return t;
}

bool TupleRaw::operator==(const TupleRaw& lhs) const {
    return doubleEquals(lhs.x(), this->x()) &&
            doubleEquals(lhs.y(), this->y()) &&
            doubleEquals(lhs.z(), this->z()) &&
            doubleEquals(lhs.w(), this->w());
}

double TupleRaw::dot(const TupleRaw& lhs, const TupleRaw& rhs) {
    return lhs._x * rhs._x +
            lhs._y * rhs._y +
            lhs._z * rhs._z +
            lhs._w * rhs._w;
}

TupleRaw TupleRaw::cross(const TupleRaw& lhs, const TupleRaw& rhs) {
    if (lhs._w != 0.0 || rhs._w != 0.0) {
        throw std::logic_error("No support for 4d vectors");
    }
    
    return TupleRaw(lhs._y * rhs._z - lhs._z * rhs._y,
                 lhs._z * rhs._x - lhs._x * rhs._z,
                 lhs._x * rhs._y - lhs._y * rhs._x,
                 0.0);
}

bool TupleRaw::doubleEquals(double a, double b) {
    return (std::abs(a - b) < 0.00001);
}

TupleRaw TupleRaw::reflect(const TupleRaw& source, const TupleRaw& normal) {
    return source - normal * 2 * dot(source, normal);
}

TupleRaw rtlib::operator+(TupleRaw lhs, const TupleRaw& rhs) {
    lhs += rhs;
    return lhs;
}

TupleRaw rtlib::operator-(TupleRaw lhs, const TupleRaw& rhs) {
    lhs -= rhs;
    return lhs;
}

TupleRaw rtlib::operator*(TupleRaw lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

TupleRaw rtlib::operator/(TupleRaw lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream& rtlib::operator<<(std::ostream& os, const TupleRaw& tuple) {
    
    os << "Tuple(" << tuple.x() << ", " << tuple.y() << ", " << tuple.z() << ", " << tuple.w() << ")";
    
    return os;
}
