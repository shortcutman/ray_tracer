//
//  ray_tests.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 27/1/2023.
//

#include <gtest/gtest.h>

#include "matrix.hpp"
#include "ray.hpp"
#include "transformations.hpp"
#include "tuple.hpp"

using namespace rtlib;

namespace {

TEST(RayTest, ConstructValidRay) {
    Ray r(create_point(0.0, 0.0, 0.0), create_vector(1.0, 1.0, 1.0));
    
    EXPECT_TRUE(r.valid());
    EXPECT_EQ(r.origin(), create_point(0.0, 0.0, 0.0));
    EXPECT_EQ(r.direction(), create_vector(1.0, 1.0, 1.0));
}

TEST(RayTest, ConstructInvalidRay) {
    Ray r1(create_vector(0.0, 0.0, 0.0), create_vector(1.0, 1.0, 1.0));
    
    EXPECT_FALSE(r1.valid());
    EXPECT_EQ(r1.origin(), create_vector(0.0, 0.0, 0.0));
    EXPECT_EQ(r1.direction(), create_vector(1.0, 1.0, 1.0));
    
    Ray r2(create_point(0.0, 0.0, 0.0), create_point(1.0, 1.0, 1.0));
    
    EXPECT_FALSE(r2.valid());
    EXPECT_EQ(r2.origin(), create_point(0.0, 0.0, 0.0));
    EXPECT_EQ(r2.direction(), create_point(1.0, 1.0, 1.0));
}

TEST(RayTest, ComputePointAtDistance) {
    Ray r(create_point(2.0, 3.0, 4.0), create_vector(1.0, 0.0, 0.0));
    
    EXPECT_EQ(r.positionAt(0.0), create_point(2.0, 3.0, 4.0));
    EXPECT_EQ(r.positionAt(1.0), create_point(3.0, 3.0, 4.0));
    EXPECT_EQ(r.positionAt(-1.0), create_point(1.0, 3.0, 4.0));
    EXPECT_EQ(r.positionAt(2.5), create_point(4.5, 3.0, 4.0));
}

TEST(RayTest, TranslateRay) {
    Ray r(create_point(1.0, 2.0, 3.0), create_vector(0.0, 1.0, 0.0));
    auto translationMatrix = rtlib::translation(3.0, 4.0, 5.0);
    auto transformedRay = r.transform(translationMatrix);
    
    EXPECT_EQ(transformedRay.origin(), create_point(4.0, 6.0, 8.0));
    EXPECT_EQ(transformedRay.direction(), create_vector(0.0, 1.0, 0.0));
}

TEST(RayTest, ScaleRay) {
    Ray r(create_point(1.0, 2.0, 3.0), create_vector(0.0, 1.0, 0.0));
    auto scaleMatrix = rtlib::scaling(2.0, 3.0, 4.0);
    auto transformedRay = r.transform(scaleMatrix);
    
    EXPECT_EQ(transformedRay.origin(), create_point(2.0, 6.0, 12.0));
    EXPECT_EQ(transformedRay.direction(), create_vector(0.0, 3.0, 0.0));
}

}
