//
//  transformation_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 15/1/2023.
//

#include <gtest/gtest.h>

#include "matrix.hpp"
#include "transformations.hpp"
#include "tuple.hpp"

namespace {

TEST(TransformationTest, MultiplyTranslationMatrixByPoint) {
    auto transform = rtlib::translation(5.0, -3.0, 2.0);
    auto point = rtlib::create_point(-3.0, 4.0, 5.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(2.0, 1.0, 7.0));
}

TEST(TransformationTest, MultiplyInverseTranslationMatrixByPoint) {
    auto transform = rtlib::translation(5.0, -3.0, 2.0);
    auto inverseTransform = transform.inverse();
    auto point = rtlib::create_point(-3.0, 4.0, 5.0);
    
    EXPECT_EQ(inverseTransform * point, rtlib::create_point(-8.0, 7.0, 3.0));
}

TEST(TransformationTest, MultiplyTranslationMatrixByVector) {
    auto transform = rtlib::translation(5.0, -3.0, 2.0);
    auto vector = rtlib::create_vector(-3.0, 4.0, 5.0);
    
    EXPECT_EQ(transform * vector, vector);
}


}