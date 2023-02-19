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

Ray _lastRay;
Tuple _lastNormalPoint;

class ObjectMock : public Object {
public:
    ObjectMock() {}
    
protected:
    virtual Intersections intersectsImpl(const Ray& ray) const {
        _lastRay = ray;
        return Intersections();
    }
    
    virtual Tuple normalAtImpl(const Tuple& point) const {
        _lastNormalPoint = point;
        auto testVec = point;
        testVec.setW(0.0);
        return testVec;
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

TEST(ObjectTest, IntersectScaledShapeWithRay) {
    ObjectMock o;
    auto ray = Ray(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    o.setTransform(scaling(2.0, 2.0, 2.0));
    o.intersects(ray);
    
    EXPECT_EQ(_lastRay.origin(), create_point(0.0, 0.0, -2.5));
    EXPECT_EQ(_lastRay.direction(), create_vector(0.0, 0.0, 0.5));
}

TEST(ObjectTest, IntersectTranslatedShapeWithRay) {
    ObjectMock o;
    auto ray = Ray(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    o.setTransform(translation(5.0, 0.0, 0.0));
    o.intersects(ray);
    
    EXPECT_EQ(_lastRay.origin(), create_point(-5.0, 0.0, -5.0));
    EXPECT_EQ(_lastRay.direction(), create_vector(0.0, 0.0, 1.0));
}

TEST(ObjectTest, NormalTranslatedShape) {
    ObjectMock o;
    o.setTransform(translation(0.0, 1.0, 0.0));
    auto normal = o.normalAt(create_point(0.0, 1.70711, -0.70711));
    EXPECT_EQ(normal, create_vector(0.0, 0.70711, -0.70711));
}

TEST(ObjectTest, NormalTransformedShape) {
    ObjectMock o;
    o.setTransform(scaling(1.0, 0.5, 1.0) * rotation_z(std::numbers::pi / 5.0));
    auto normal = o.normalAt(create_point(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
    EXPECT_EQ(normal, create_vector(0.0, 0.97014, -0.24254));
}

}
