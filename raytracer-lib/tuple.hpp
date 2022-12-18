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
    float _x;
    float _y;
    float _z;
    float _w;
    
public:
    Tuple();
    Tuple(float x, float y, float z);
    Tuple(float x, float y, float z, float w);
    ~Tuple() {};
    
    float x() const;
    float y() const;
    float z() const;
    float w() const;
    
    bool isPoint() const;
    bool isVector() const;
};

}


#endif /* tuple_hpp */
