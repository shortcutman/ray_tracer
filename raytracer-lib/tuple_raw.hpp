//
//  tuple.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#ifndef tuple_raw_hpp
#define tuple_raw_hpp

#include <cstddef>
#include <ostream>

namespace rtlib {

class TupleRaw {
protected:
    double _x;
    double _y;
    double _z;
    double _w;
        
public:
    TupleRaw();
    TupleRaw(const TupleRaw& t) = default;
    TupleRaw(double x, double y, double z);
    TupleRaw(double x, double y, double z, double w);
    ~TupleRaw() {};
    
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
    
    TupleRaw& operator+=(const TupleRaw& rhs);
    TupleRaw& operator-=(const TupleRaw& rhs);
    TupleRaw& operator*=(double rhs);
    TupleRaw& operator/=(double rhs);
    TupleRaw operator-();
    TupleRaw normalised() const;
    
    bool operator==(const TupleRaw& lhs) const;
    
    static double dot(const TupleRaw& lhs, const TupleRaw& rhs);
    static TupleRaw cross(const TupleRaw& lhs, const TupleRaw& rhs);
    static bool doubleEquals(double a, double b);
    static TupleRaw reflect(const TupleRaw& source, const TupleRaw& normal);
};

TupleRaw operator+(TupleRaw lhs, const TupleRaw& rhs);
TupleRaw operator-(TupleRaw lhs, const TupleRaw& rhs);
TupleRaw operator*(TupleRaw lhs, double rhs);
TupleRaw operator/(TupleRaw lhs, double rhs);

std::ostream& operator<< (std::ostream& os, const TupleRaw& matrix);

}


#endif /* tuple_raw_hpp */
