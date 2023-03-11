//
//  pattern_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 5/3/2023.
//

#include <gtest/gtest.h>

#include "pattern.hpp"

#include "lighting.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "transformations.hpp"

#include "PointObject.hpp"

using namespace rtlib;

namespace {

TEST(PatternTest, StripePatternConstantInY) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto obj = rtlib_tests::PointObject();
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 1.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 2.0, 0.0)), white);
}

TEST(PatternTest, StripePatternConstantInZ) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto obj = rtlib_tests::PointObject();
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 0.0, 1.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 0.0, 2.0)), white);
}

TEST(PatternTest, StripePatternAlternatesInX) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto obj = rtlib_tests::PointObject();
    auto stripePattern = StripePattern(white, black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(0.9, 0.0, 0.0)), white);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(1.0, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(-0.1, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(-1.0, 0.0, 0.0)), black);
    EXPECT_EQ(stripePattern.colourAt(&obj, create_point(-1.1, 0.0, 0.0)), white);
}

TEST(PatternTest, StripePatternWithLightApplied) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto point = rtlib_tests::PointObject();
    auto material = Material({
        std::make_shared<StripePattern>(white, black),
        Colour(1.0, 0.0, 0.0),
        1.0,
        0.0,
        0.0,
    });
    point.setMaterial(material);
    auto eyeV = create_vector(0.0, 0.0, -1.0);
    auto normalV = create_vector(0.0, 0.0, -1.0);
    
    auto light = Light(create_point(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));
    EXPECT_EQ(light.lightPoint(&point, create_point(0.9, 0.0, 0.0), eyeV, normalV, false), Colour(1.0, 1.0, 1.0));
    EXPECT_EQ(light.lightPoint(&point, create_point(1.1, 0.0, 0.0), eyeV, normalV, false), Colour(0.0, 0.0, 0.0));
}

TEST(PatternTest, StripePatternWithObjectTransformation) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto sphere = Sphere();
    auto material = Material({
        std::make_shared<StripePattern>(white, black),
        Colour(1.0, 0.0, 0.0),
        1.0,
        0.0,
        0.0,
    });
    sphere.setMaterial(material);
    sphere.setTransform(scaling(2.0, 2.0, 2.0));
    
    EXPECT_EQ(sphere.material().colourAt(&sphere, create_point(1.5, 0.0, 0.0)), white);
}

TEST(PatternTest, StripePatternWithPatternTransformation) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto sphere = Sphere();
    auto material = Material({
        std::make_shared<StripePattern>(white, black),
        Colour(1.0, 0.0, 0.0),
        1.0,
        0.0,
        0.0,
    });
    material._pattern->setTransform(scaling(2.0, 2.0, 2.0));
    sphere.setMaterial(material);
    
    EXPECT_EQ(sphere.material().colourAt(&sphere, create_point(1.5, 0.0, 0.0)), white);
}

TEST(PatternTest, StripePatternWithObjectAndPatternTransformation) {
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    
    auto sphere = Sphere();
    sphere.setTransform(scaling(2.0, 2.0, 2.0));
    auto material = Material({
        std::make_shared<StripePattern>(white, black),
        Colour(1.0, 0.0, 0.0),
        1.0,
        0.0,
        0.0,
    });
    material._pattern->setTransform(translation(0.5, 0.0, 0.0));
    sphere.setMaterial(material);
    
    EXPECT_EQ(sphere.material().colourAt(&sphere, create_point(2.5, 0.0, 0.0)), white);
}

TEST(PatternTest, GradientPatternLinearColourInterpolation) {
    auto point = rtlib_tests::PointObject();
    
    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);
    auto gradient = GradientPattern(white, black);
    EXPECT_EQ(gradient.colourAt(&point, create_point(0.0, 0.0, 0.0)), white);
    EXPECT_EQ(gradient.colourAt(&point, create_point(0.25, 0.0, 0.0)), Colour(0.75, 0.75, 0.75));
    EXPECT_EQ(gradient.colourAt(&point, create_point(0.5, 0.0, 0.0)), Colour(0.5, 0.5, 0.5));
    EXPECT_EQ(gradient.colourAt(&point, create_point(0.75, 0.0, 0.0)), Colour(0.25, 0.25, 0.25));
}

}
