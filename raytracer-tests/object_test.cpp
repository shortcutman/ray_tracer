//
//  object_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 27/1/2023.
//

#include <gtest/gtest.h>

#include "object.hpp"
#include "ray.hpp"

namespace {

TEST(ObjectTest, IntersectSphereThroughMiddle) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, 4.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 6.0);
}

TEST(ObjectTest, IntersectSphereTangent) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 1.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, 5.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 5.0);
}

TEST(ObjectTest, IntersectSphereMiss) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 2.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 0);
}

TEST(ObjectTest, IntersectSphereFromInside) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, 0.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, -1.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 1.0);
}

TEST(ObjectTest, IntersectSphereBehind) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, 5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, -6.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, -4.0);
}

}
