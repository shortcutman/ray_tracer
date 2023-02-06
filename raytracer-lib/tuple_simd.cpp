//
//  tuple.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "tuple_simd.hpp"

#include <cmath>
#include <stdexcept>

using namespace rtlib;

TupleSimd::TupleSimd() :
    _vector(simd_make_double4(0.0, 0.0, 0.0, 0.0))
{
}

TupleSimd::TupleSimd(double x, double y, double z) :
    _vector(simd_make_double4(x, y, z, 0.0))
{
}

TupleSimd::TupleSimd(double x, double y, double z, double w) :
    _vector(simd_make_double4(x, y, z, w))
{
}

double TupleSimd::x() const {
    return _vector.x;
}

double TupleSimd::y() const {
    return _vector.y;
}

double TupleSimd::z() const {
    return _vector.z;
}

double TupleSimd::w() const {
    return _vector.w;
}

void TupleSimd::setX(double x) {
    _vector.x = x;
}

void TupleSimd::setY(double y) {
    _vector.y = y;
}

void TupleSimd::setZ(double z) {
    _vector.z = z;
}

void TupleSimd::setW(double w) {
    _vector.w = w;
}

double TupleSimd::operator[](size_t index) const {
    switch (index) {
        case 0:
            return _vector.x;
            
        case 1:
            return _vector.y;
            
        case 2:
            return _vector.z;
            
        case 3:
            return _vector.w;
    }
    
    throw std::runtime_error("index out of range");
    return 0.0;
}

void TupleSimd::set(size_t index, double value) {
    switch (index) {
        case 0:
            _vector.x = value;
            return;
            
        case 1:
            _vector.y = value;
            return;
            
        case 2:
            _vector.z = value;
            return;
            
        case 3:
            _vector.w = value;
            return;
    }
    
    throw std::runtime_error("index out of range");
}

double TupleSimd::magnitude() const {
    return simd_length(_vector);
}

bool TupleSimd::isPoint() const {
    return _vector.w == 1.0;
}

bool TupleSimd::isVector() const {
    return _vector.w == 0.0;
}

TupleSimd& TupleSimd::operator+=(const TupleSimd& rhs) {
    this->_vector += rhs._vector;
    return *this;
}

TupleSimd& TupleSimd::operator-=(const TupleSimd& rhs) {
    this->_vector -= rhs._vector;
    return *this;
}

TupleSimd& TupleSimd::operator*=(double rhs) {
    this->_vector *= rhs;
    return *this;
}

TupleSimd& TupleSimd::operator/=(double rhs) {
    this->_vector /= rhs;
    return *this;
}

TupleSimd TupleSimd::operator-() {
    auto t = *this;
    t._vector *= -1.0;
    return t;
}

TupleSimd TupleSimd::normalised() const {
    auto t = *this;
    t._vector = simd_normalize(t._vector);
    return t;
}

bool TupleSimd::operator==(const TupleSimd& lhs) const {
    return doubleEquals(lhs.x(), this->x()) &&
            doubleEquals(lhs.y(), this->y()) &&
            doubleEquals(lhs.z(), this->z()) &&
            doubleEquals(lhs.w(), this->w());
}

double TupleSimd::dot(const TupleSimd& lhs, const TupleSimd& rhs) {
    return simd_dot(lhs._vector, rhs._vector);
}

TupleSimd TupleSimd::cross(const TupleSimd& lhs, const TupleSimd& rhs) {
    if (lhs.w() != 0.0 || rhs.w() != 0.0) {
        throw std::logic_error("No support for 4d vectors");
    }
    
    auto threeD1 = simd_make_double3(lhs._vector.x, lhs._vector.y, lhs._vector.z);
    auto threeD2 = simd_make_double3(rhs._vector.x, rhs._vector.y, rhs._vector.z);
    auto result = simd_cross(threeD1, threeD2);
    
    return TupleSimd(result.x, result.y, result.z);
}

bool TupleSimd::doubleEquals(double a, double b) {
    return (std::abs(a - b) < 0.00001);
}

TupleSimd TupleSimd::reflect(const TupleSimd& source, const TupleSimd& normal) {
    auto t = source;
    t._vector = simd_reflect(source._vector, normal._vector);
    return t;
}

TupleSimd rtlib::operator+(TupleSimd lhs, const TupleSimd& rhs) {
    lhs += rhs;
    return lhs;
}

TupleSimd rtlib::operator-(TupleSimd lhs, const TupleSimd& rhs) {
    lhs -= rhs;
    return lhs;
}

TupleSimd rtlib::operator*(TupleSimd lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

TupleSimd rtlib::operator/(TupleSimd lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream& rtlib::operator<<(std::ostream& os, const TupleSimd& tuple) {
    
    os << "Tuple(" << tuple.x() << ", " << tuple.y() << ", " << tuple.z() << ", " << tuple.w() << ")";
    
    return os;
}
