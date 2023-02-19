//
//  object_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 19/2/2023.
//

#include <gtest/gtest.h>

#include "object.hpp"
#include "transformations.hpp"

#include <cmath>
#include <numbers>
#include <limits>

using namespace rtlib;

namespace {

class ObjectMock : public Object {
public:
    virtual Intersections intersects(const Ray& ray) const {
        return Intersections();
    }
    
    virtual Tuple normalAt(const Tuple& point) const {
        return Tuple();
    };

};

TEST(ObjectTest, DefaultTransformation) {
    ObjectMock o;
    
    EXPECT_EQ(o.transform(), Matrix4x4::identityMatrix());
}

TEST(ObjectTest, AssignTransformation) {
    ObjectMock o;
    o.setTransform(translation(2.0, 3.0, 4.0));
    
    EXPECT_EQ(o.transform(), translation(2.0, 3.0, 4.0));
}

TEST(ObjectTest, DefaultMaterial) {
    ObjectMock o;
    Material m;
    EXPECT_EQ(o.material()._colour, m._colour);
    EXPECT_EQ(o.material()._ambient, m._ambient);
    EXPECT_EQ(o.material()._diffuse, m._diffuse);
    EXPECT_EQ(o.material()._specular, m._specular);
    EXPECT_EQ(o.material()._shininess, m._shininess);
}

TEST(ObjectTest, AssignMaterialViaSetter) {
    ObjectMock o;
    Material m = {
        Colour(0.1, 0.2, 0.3),
        0.2,
        0.3,
        0.4,
        0.5
    };
    o.setMaterial(m);
    EXPECT_EQ(o.material()._colour, m._colour);
    EXPECT_EQ(o.material()._ambient, m._ambient);
    EXPECT_EQ(o.material()._diffuse, m._diffuse);
    EXPECT_EQ(o.material()._specular, m._specular);
    EXPECT_EQ(o.material()._shininess, m._shininess);
}

TEST(ObjectTest, AssignMaterialViaReference) {
    ObjectMock o;
    o.material()._colour = Colour(0.1, 0.2, 0.3);
    o.material()._ambient = 0.2;
    o.material()._diffuse = 0.3;
    o.material()._specular = 0.4;
    o.material()._shininess = 0.5;
    EXPECT_EQ(o.material()._colour, Colour(0.1, 0.2, 0.3));
    EXPECT_EQ(o.material()._ambient, 0.2);
    EXPECT_EQ(o.material()._diffuse, 0.3);
    EXPECT_EQ(o.material()._specular, 0.4);
    EXPECT_EQ(o.material()._shininess, 0.5);
}

}
