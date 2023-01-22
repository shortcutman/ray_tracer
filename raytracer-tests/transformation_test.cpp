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

#include <cmath>
#include <numbers>

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

TEST(TransformationTest, MultiplyScalingMatrixByPoint) {
    auto transform = rtlib::scaling(2.0, 3.0, 4.0);
    auto point = rtlib::create_point(-4.0, 6.0, 8.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(-8.0, 18.0, 32.0));
}

TEST(TransformationTest, MultiplyScalingMatrixByVector) {
    auto transform = rtlib::scaling(2.0, 3.0, 4.0);
    auto vector = rtlib::create_vector(-4.0, 6.0, 8.0);
    
    EXPECT_EQ(transform * vector, rtlib::create_vector(-8.0, 18.0, 32.0));
}

TEST(TransformationTest, MultiplyInverseScalingMatrixByVector) {
    auto transform = rtlib::scaling(2.0, 3.0, 4.0);
    auto inverseTransform = transform.inverse();
    auto vector = rtlib::create_vector(-4.0, 6.0, 8.0);

    EXPECT_EQ(inverseTransform * vector, rtlib::create_vector(-2.0, 2.0, 2.0));
}

TEST(TransformationTest, MultiplyScalingMatrixAsReflectionByPoint) {
    auto transform = rtlib::scaling(-1.0, 1.0, 1.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(-2.0, 3.0, 4.0));
}

TEST(TransformationTest, MultiplyRotationXMatrixByPoint) {
    auto point = rtlib::create_point(0.0, 1.0, 0.0);
    
    auto half_quarter = rtlib::rotation_x(std::numbers::pi / 4.0);
    EXPECT_EQ(half_quarter * point, rtlib::create_point(0.0, std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
    
    auto full_quarter = rtlib::rotation_x(std::numbers::pi / 2.0);
    EXPECT_EQ(full_quarter * point, rtlib::create_point(0.0, 0.0, 1.0));
}

TEST(TransformationTest, MultiplyInverseRotationXMatrixByPoint) {
    auto point = rtlib::create_point(0.0, 1.0, 0.0);
    
    auto half_quarter = rtlib::rotation_x(std::numbers::pi / 4.0);
    auto inverse = half_quarter.inverse();
    EXPECT_EQ(half_quarter * point, rtlib::create_point(0.0, std::sqrt(2) / 2.0, 1.0 * std::sqrt(2) / 2.0));
}

TEST(TransformationTest, MultiplyRotationYMatrixByPoint) {
    auto point = rtlib::create_point(0.0, 0.0, 1.0);
    
    auto half_quarter = rtlib::rotation_y(std::numbers::pi / 4.0);
    EXPECT_EQ(half_quarter * point, rtlib::create_point(std::sqrt(2) / 2.0, 0.0, std::sqrt(2) / 2.0));
    
    auto full_quarter = rtlib::rotation_y(std::numbers::pi / 2.0);
    EXPECT_EQ(full_quarter * point, rtlib::create_point(1.0, 0.0, 0.0));
}

TEST(TransformationTest, MultiplyRotationZMatrixByPoint) {
    auto point = rtlib::create_point(0.0, 1.0, 0.0);
    
    auto half_quarter = rtlib::rotation_z(std::numbers::pi / 4.0);
    EXPECT_EQ(half_quarter * point, rtlib::create_point(-1.0 * std::sqrt(2) / 2.0, std::sqrt(2) / 2.0, 0.0));
    
    auto full_quarter = rtlib::rotation_z(std::numbers::pi / 2.0);
    EXPECT_EQ(full_quarter * point, rtlib::create_point(-1.0, 0.0, 0.0));
}

TEST(TransformationTest, MultiplyShearXtoYMatrixByPoint) {
    auto transform = rtlib::shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(5.0, 3.0, 4.0));
}

TEST(TransformationTest, MultiplyShearXtoZMatrixByPoint) {
    auto transform = rtlib::shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(6.0, 3.0, 4.0));
}

TEST(TransformationTest, MultiplyShearYtoXMatrixByPoint) {
    auto transform = rtlib::shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(2.0, 5.0, 4.0));
}

TEST(TransformationTest, MultiplyShearYtoZMatrixByPoint) {
    auto transform = rtlib::shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(2.0, 7.0, 4.0));
}

TEST(TransformationTest, MultiplyShearZtoXMatrixByPoint) {
    auto transform = rtlib::shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(2.0, 3.0, 6.0));
}

TEST(TransformationTest, MultiplyShearZtoYMatrixByPoint) {
    auto transform = rtlib::shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    auto point = rtlib::create_point(2.0, 3.0, 4.0);
    
    EXPECT_EQ(transform * point, rtlib::create_point(2.0, 3.0, 7.0));
}

TEST(TransformationTest, IndividualTransformationsAppliedInSequence) {
    auto point = rtlib::create_point(1.0, 0.0, 1.0);

    auto rotate = rtlib::rotation_x(std::numbers::pi / 2.0);
    auto scale = rtlib::scaling(5.0, 5.0, 5.0);
    auto translate = rtlib::translation(10.0, 5.0, 7.0);
    
    auto step1 = rotate * point;
    EXPECT_EQ(step1, rtlib::create_point(1.0, -1.0, 0.0));
    
    auto step2 = scale * step1;
    EXPECT_EQ(step2, rtlib::create_point(5.0, -5.0, 0.0));
    
    auto step3 = translate * step2;
    EXPECT_EQ(step3, rtlib::create_point(15.0, 0.0, 7.0));
}

TEST(TransformationTest, ChainedTransformationsAppliedInReverse) {
    auto point = rtlib::create_point(1.0, 0.0, 1.0);

    auto rotate = rtlib::rotation_x(std::numbers::pi / 2.0);
    auto scale = rtlib::scaling(5.0, 5.0, 5.0);
    auto translate = rtlib::translation(10.0, 5.0, 7.0);
    
    auto combinedTransform = translate * scale * rotate;
    EXPECT_EQ(combinedTransform * point, rtlib::create_point(15.0, 0.0, 7.0));
}

}
