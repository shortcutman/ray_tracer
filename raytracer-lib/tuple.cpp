//
//  tuple.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "tuple.hpp"

#include <cmath>
#include <stdexcept>

using namespace rtlib;

Tuple::Tuple() :
    _x(0.0),
    _y(0.0),
    _z(0.0),
    _w(0.0) {
}

Tuple::Tuple(double x, double y, double z) :
    _x(x),
    _y(y),
    _z(z),
    _w(0.0) {
}

Tuple::Tuple(double x, double y, double z, double w) :
    _x(x),
    _y(y),
    _z(z),
    _w(w) {
}

double Tuple::x() const {
    return _x;
}

double Tuple::y() const {
    return _y;
}

double Tuple::z() const {
    return _z;
}

double Tuple::w() const {
    return _w;
}

void Tuple::setX(double x) {
    _x = x;
}

void Tuple::setY(double y) {
    _y = y;
}

void Tuple::setZ(double z) {
    _z = z;
}

void Tuple::setW(double w) {
    _w = w;
}

double Tuple::operator[](size_t index) const {
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

double& Tuple::operator[](size_t index) {
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
    return _x;
}


double Tuple::magnitude() const {
    return std::sqrt(std::pow(_x, 2) +
                     std::pow(_y, 2) +
                     std::pow(_z, 2) +
                     std::pow(_w, 2));
}

bool Tuple::isPoint() const {
    return _w == 1.0;
}

bool Tuple::isVector() const {
    return _w == 0.0;
}

Tuple& Tuple::operator+=(const Tuple& rhs) {
    this->_x += rhs.x();
    this->_y += rhs.y();
    this->_z += rhs.z();
    this->_w += rhs.w();
    return *this;
}

Tuple& Tuple::operator-=(const Tuple& rhs) {
    this->_x -= rhs.x();
    this->_y -= rhs.y();
    this->_z -= rhs.z();
    this->_w -= rhs.w();
    return *this;
}

Tuple& Tuple::operator*=(double rhs) {
    this->_x *= rhs;
    this->_y *= rhs;
    this->_z *= rhs;
    this->_w *= rhs;
    return *this;
}

Tuple& Tuple::operator/=(double rhs) {
    this->_x /= rhs;
    this->_y /= rhs;
    this->_z /= rhs;
    this->_w /= rhs;
    return *this;
}

Tuple Tuple::operator-() {
    auto t = *this;
    t._x *= -1.0;
    t._y *= -1.0;
    t._z *= -1.0;
    t._w *= -1.0;
    return t;
}

void Tuple::normalise() {
    auto magnitude = this->magnitude();
    this->_x /= magnitude;
    this->_y /= magnitude;
    this->_z /= magnitude;
    this->_w /= magnitude;
}

Tuple Tuple::createNormalized() const {
    auto t = *this;
    t.normalise();
    return t;
}

bool Tuple::operator==(const Tuple& lhs) const {
    return doubleEquals(lhs.x(), this->x()) &&
            doubleEquals(lhs.y(), this->y()) &&
            doubleEquals(lhs.z(), this->z()) &&
            doubleEquals(lhs.w(), this->w());
}

double Tuple::dot(const Tuple& lhs, const Tuple& rhs) {
    return lhs._x * rhs._x +
            lhs._y * rhs._y +
            lhs._z * rhs._z +
            lhs._w * rhs._w;
}

Tuple Tuple::cross(const Tuple& lhs, const Tuple& rhs) {
    if (lhs._w != 0.0 || rhs._w != 0.0) {
        throw std::logic_error("No support for 4d vectors");
    }
    
    return create_vector(lhs._y * rhs._z - lhs._z * rhs._y,
                         lhs._z * rhs._x - lhs._x * rhs._z,
                         lhs._x * rhs._y - lhs._y * rhs._x);
}

bool Tuple::doubleEquals(double a, double b) {
    return (std::abs(a - b) < 0.00001);
}

Tuple rtlib::operator+(Tuple lhs, const Tuple& rhs) {
    lhs += rhs;
    return lhs;
}

Tuple rtlib::operator-(Tuple lhs, const Tuple& rhs) {
    lhs -= rhs;
    return lhs;
}

Tuple rtlib::operator*(Tuple lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

Tuple rtlib::operator/(Tuple lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream& rtlib::operator<<(std::ostream& os, const Tuple& tuple) {
    
    os << "Tuple(" << tuple.x() << ", " << tuple.y() << ", " << tuple.z() << ", " << tuple.w() << ")";
    
    return os;
}

Tuple rtlib::create_point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

Tuple rtlib::create_vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}
