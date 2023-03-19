//
//  TestPattern.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 19/3/2023.
//

#include "TestPattern.hpp"

rtlib::Colour rtlib_tests::TestPattern::colourAtLocalPoint(rtlib::Tuple point) const {
    return rtlib::Colour(point.x(), point.y(), point.z());
}

#include <gtest/gtest.h>

#include "sphere.hpp"
#include "transformations.hpp"

namespace {

TEST(TestPattern, PatternWithObjectTransformation) {
    auto sphere = rtlib::Sphere();
    sphere.setTransform(rtlib::scaling(2.0, 2.0, 2.0));
    auto pattern = rtlib_tests::TestPattern();
    
    auto colour = pattern.colourAt(&sphere, rtlib::create_point(2.0, 3.0, 4.0));
    
    EXPECT_EQ(colour, rtlib::Colour(1.0, 1.5, 2.0));
}

TEST(TestPattern, PatternWithAPatternTransformation) {
    auto sphere = rtlib::Sphere();
    auto pattern = rtlib_tests::TestPattern();
    pattern.setTransform(rtlib::scaling(2.0, 2.0, 2.0));
    
    auto colour = pattern.colourAt(&sphere, rtlib::create_point(2.0, 3.0, 4.0));
    
    EXPECT_EQ(colour, rtlib::Colour(1.0, 1.5, 2.0));
}

TEST(TestPattern, PatternWithObjectAndPatternTransformation) {
    auto sphere = rtlib::Sphere();
    sphere.setTransform(rtlib::scaling(2.0, 2.0, 2.0));
    auto pattern = rtlib_tests::TestPattern();
    pattern.setTransform(rtlib::translation(0.5, 1.0, 1.5));
    
    auto colour = pattern.colourAt(&sphere, rtlib::create_point(2.5, 3.0, 3.5));
    
    EXPECT_EQ(colour, rtlib::Colour(0.75, 0.5, 0.25));
}

}
