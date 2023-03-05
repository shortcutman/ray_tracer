//
//  PointObject.hpp
//  raytracer-tests
//
//  Created by Daniel Burke on 5/3/2023.
//

#ifndef PointObject_hpp
#define PointObject_hpp

#include "object.hpp"

namespace rtlib_tests {

class PointObject : public rtlib::Object {
protected:
    virtual rtlib::Intersections intersectsImpl(const rtlib::Ray& ray) const;
    virtual rtlib::Tuple normalAtImpl(const rtlib::Tuple& point) const;
};

}

#endif /* PointObject_hpp */
