//
//  tuple.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#ifndef tuple_hpp
#define tuple_hpp

#include <cstddef>
#include <ostream>

namespace rtlib {

class Tuple {
protected:
    double _x;
    double _y;
    double _z;
    double _w;
    
public:
    Tuple();
    Tuple(const Tuple& t) = default;
    Tuple(double x, double y, double z);
    Tuple(double x, double y, double z, double w);
    ~Tuple() {};
    
    double x() const;
    double y() const;
    double z() const;
    double w() const;
    
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);
    double operator[](std::size_t index) const;
    double& operator[](std::size_t index);
    
    double magnitude() const;
    bool isPoint() const;
    bool isVector() const;
    
    Tuple& operator+=(const Tuple& rhs);
    Tuple& operator-=(const Tuple& rhs);
    Tuple& operator*=(double rhs);
    Tuple& operator/=(double rhs);
    Tuple operator-();
    void normalise();
    Tuple createNormalized() const;
    
    bool operator==(const Tuple& lhs) const;
    
    static double dot(const Tuple& lhs, const Tuple& rhs);
    static Tuple cross(const Tuple& lhs, const Tuple& rhs);
    static bool doubleEquals(double a, double b);
};

Tuple operator+(Tuple lhs, const Tuple& rhs);
Tuple operator-(Tuple lhs, const Tuple& rhs);
Tuple operator*(Tuple lhs, double rhs);
Tuple operator/(Tuple lhs, double rhs);

std::ostream& operator<< (std::ostream& os, const Tuple& matrix);

Tuple create_point(double x, double y, double z);
Tuple create_vector(double x, double y, double z);

}


#endif /* tuple_hpp */
