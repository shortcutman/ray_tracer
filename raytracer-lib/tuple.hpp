//
//  tuple.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 18/12/2022.
//

#ifndef tuple_hpp
#define tuple_hpp

namespace rtlib {

class Tuple {
private:
    double _x;
    double _y;
    double _z;
    double _w;
    
public:
    Tuple();
    Tuple(double x, double y, double z);
    Tuple(double x, double y, double z, double w);
    ~Tuple() {};
    
    double x() const;
    double y() const;
    double z() const;
    double w() const;
    
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

Tuple create_point(double x, double y, double z);
Tuple create_vector(double x, double y, double z);

}


#endif /* tuple_hpp */
