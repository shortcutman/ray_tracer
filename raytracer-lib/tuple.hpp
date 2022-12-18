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
    
    bool isPoint() const;
    bool isVector() const;
    
    bool operator==(const Tuple& lhs) const;
};

Tuple create_point(double x, double y, double z);
Tuple create_vector(double x, double y, double z);

}


#endif /* tuple_hpp */
