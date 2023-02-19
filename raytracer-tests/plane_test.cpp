//
//  plane_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 19/2/2023.
//

#include <gtest/gtest.h>

#include "plane.hpp"

using namespace rtlib;

namespace {

TEST(PlaneTest, NormalConstantEverywhere) {
    Plane p;
    
    auto n1 = p.normalAt(create_point(0.0, 0.0, 0.0));
    EXPECT_EQ(n1, create_vector(0.0, 1.0, 0.0));
    
    auto n2 = p.normalAt(create_point(10.0, 0.0, -10.0));
    EXPECT_EQ(n2, create_vector(0.0, 1.0, 0.0));
    
    auto n3 = p.normalAt(create_point(-5.0, 0.0, 150.0));
    EXPECT_EQ(n3, create_vector(0.0, 1.0, 0.0));
}

TEST(PlaneTest, IntersectWithRayParallelToPlaneAndWillNeverIntersect) {
    Plane p;
    auto ray = Ray(create_point(0.0, 10.0, 0.0), create_vector(0.0, 0.0, 1.0));
    auto intersections = p.intersects(ray);
    EXPECT_TRUE(intersections.empty());
}

TEST(PlaneTest, IntersectWithRayCoplanarToPlaneAssumeNeverIntersect) {
    Plane p;
    auto ray = Ray(create_point(0.0, 0.0, 0.0), create_vector(0.0, 0.0, 1.0));
    auto intersections = p.intersects(ray);
    EXPECT_TRUE(intersections.empty());
}

TEST(PlaneTest, IntersectWithRayFromAbove) {
    Plane p;
    auto ray = Ray(create_point(0.0, 1.0, 0.0), create_vector(0.0, -1.0, 0.0));
    auto intersections = p.intersects(ray);
    EXPECT_EQ(intersections.size(), 1);
    EXPECT_EQ(intersections.front().t, 1.0);
    EXPECT_EQ(intersections.front().object, &p);
}

TEST(PlaneTest, IntersectWithRayFromBelow) {
    Plane p;
    auto ray = Ray(create_point(0.0, -1.0, 0.0), create_vector(0.0, 1.0, 0.0));
    auto intersections = p.intersects(ray);
    EXPECT_EQ(intersections.size(), 1);
    EXPECT_EQ(intersections.front().t, 1.0);
    EXPECT_EQ(intersections.front().object, &p);
}

}
