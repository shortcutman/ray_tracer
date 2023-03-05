//
//  pattern_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 5/3/2023.
//

#include <gtest/gtest.h>

#include "pattern.hpp"

using namespace rtlib;

namespace {

TEST(PatternTest, StripePatternConstantInY) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 1.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 2.0, 0.0)), white);
}

TEST(PatternTest, StripePatternConstantInZ) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 0.0, 1.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 0.0, 2.0)), white);
}

TEST(PatternTest, StripePatternAlternatesInX) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(0.9, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(create_point(1.0, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(create_point(-0.1, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(create_point(-1.0, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(create_point(-1.1, 0.0, 0.0)), white);
}

}

