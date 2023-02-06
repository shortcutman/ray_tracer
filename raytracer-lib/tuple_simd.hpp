//
//  tuple.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#ifndef tuple_simd_hpp
#define tuple_simd_hpp

#include <cstddef>
#include <ostream>
#include <simd/simd.h>

namespace rtlib {

class TupleSimd {
protected:
    simd_double4 _vector;
        
public:
    TupleSimd();
    TupleSimd(const TupleSimd& t) = default;
    TupleSimd(double x, double y, double z);
    TupleSimd(double x, double y, double z, double w);
    ~TupleSimd() {};
    
    double x() const;
    double y() const;
    double z() const;
    double w() const;
    
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);
    double operator[](std::size_t index) const;
    void set(std::size_t index, double value);
    
    double magnitude() const;
    bool isPoint() const;
    bool isVector() const;
    
    TupleSimd& operator+=(const TupleSimd& rhs);
    TupleSimd& operator-=(const TupleSimd& rhs);
    TupleSimd& operator*=(double rhs);
    TupleSimd& operator/=(double rhs);
    TupleSimd operator-();
    TupleSimd normalised() const;
    
    bool operator==(const TupleSimd& lhs) const;
    
    static double dot(const TupleSimd& lhs, const TupleSimd& rhs);
    static TupleSimd cross(const TupleSimd& lhs, const TupleSimd& rhs);
    static bool doubleEquals(double a, double b);
    static TupleSimd reflect(const TupleSimd& source, const TupleSimd& normal);
};

TupleSimd operator+(TupleSimd lhs, const TupleSimd& rhs);
TupleSimd operator-(TupleSimd lhs, const TupleSimd& rhs);
TupleSimd operator*(TupleSimd lhs, double rhs);
TupleSimd operator/(TupleSimd lhs, double rhs);

std::ostream& operator<< (std::ostream& os, const TupleSimd& matrix);

}


#endif /* tuple_simd_hpp */
