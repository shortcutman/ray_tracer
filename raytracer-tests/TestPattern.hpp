//
//  TestPattern.hpp
//  raytracer-tests
//
//  Created by Daniel Burke on 19/3/2023.
//

#ifndef TestPattern_hpp
#define TestPattern_hpp

#include "pattern.hpp"

namespace rtlib_tests {

class TestPattern : public rtlib::Pattern {
protected:
    virtual rtlib::Colour colourAtLocalPoint(rtlib::Tuple point) const;
};

}

#endif /* TestPattern_hpp */
