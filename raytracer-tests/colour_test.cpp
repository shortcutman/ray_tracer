//
//  colour_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 23/12/2022.
//

#include <gtest/gtest.h>

#include "colour.hpp"
#include "tuple.hpp"

namespace {

TEST(ColourTest, CreateColour) {
    rtlib::Colour c(-0.5, 0.4, 1.7);
    
    EXPECT_DOUBLE_EQ(c.red(), -0.5);
    EXPECT_DOUBLE_EQ(c.green(), 0.4);
    EXPECT_DOUBLE_EQ(c.blue(), 1.7);
}

TEST(ColourTest, AddColours) {
    rtlib::Colour c1(0.9, 0.6, 0.75);
    rtlib::Colour c2(0.7, 0.1, 0.25);
    
    rtlib::Colour c3 = c1 + c2;
    
    EXPECT_DOUBLE_EQ(c3.red(), 1.6);
    EXPECT_DOUBLE_EQ(c3.green(), 0.7);
    EXPECT_DOUBLE_EQ(c3.blue(), 1.0);
}

TEST(ColourTest, SubtractColours) {
    rtlib::Colour c1(0.9, 0.6, 0.75);
    rtlib::Colour c2(0.7, 0.1, 0.25);
    
    rtlib::Colour c3 = c1 - c2;
    
    EXPECT_DOUBLE_EQ(c3.red(), 0.2);
    EXPECT_DOUBLE_EQ(c3.green(), 0.5);
    EXPECT_DOUBLE_EQ(c3.blue(), 0.5);
}

TEST(ColourTest, MultiplyColourByScalar) {
    rtlib::Colour c1(0.2, 0.3, 0.4);
    rtlib::Colour c2 = c1 * 2;
    
    EXPECT_DOUBLE_EQ(c2.red(), 0.4);
    EXPECT_DOUBLE_EQ(c2.green(), 0.6);
    EXPECT_DOUBLE_EQ(c2.blue(), 0.8);
}

TEST(ColourTest, MultiplyColourByColour) {
    rtlib::Colour c1(1.0, 0.2, 0.4);
    rtlib::Colour c2(0.9, 1.0, 0.1);
    
    rtlib::Colour c3 = c1 * c2;
    
    EXPECT_DOUBLE_EQ(c3.red(), 0.9);
    EXPECT_DOUBLE_EQ(c3.green(), 0.2);
    EXPECT_DOUBLE_EQ(c3.blue(), 0.04);
}

}
