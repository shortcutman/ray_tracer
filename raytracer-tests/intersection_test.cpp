//
//  intersection_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 11/3/2023.
//

#include <gtest/gtest.h>

#include "intersection.hpp"

#include "plane.hpp"
#include "ray.hpp"

using namespace rtlib;

namespace {

TEST(IntersectionTest, PrecomputeReflectionVector) {
    auto plane = Plane();
    auto ray = Ray(create_point(0.0, 0.0, 0.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersect = Intersect(&plane, std::sqrt(2.0));
    auto intersectValues = IntersectValues(intersect, ray);
    
    EXPECT_EQ(intersectValues.reflectionVector, create_vector(0.0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
}

}
