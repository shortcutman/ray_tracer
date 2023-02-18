//
//  lighting_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 3/2/2023.
//

#include <gtest/gtest.h>

#include "lighting.hpp"

#include <cmath>

namespace {

TEST(LightingTest, LightConstruction) {

    auto origin = rtlib::create_point(1.0, 0.0, 0.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(origin, intensity);
    
    EXPECT_EQ(light.origin(), origin);
    EXPECT_EQ(light.intensity(), intensity);
}

TEST(LightingTest, MaterialConstruction) {
}

TEST(LightingTest, LightPointWithEyeBetweenLightAndSurface) {
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    auto eye = rtlib::create_vector(0.0, 0.0, -1.0);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 0.0, -10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, false);
    EXPECT_EQ(result.red(), 1.9);
    EXPECT_EQ(result.green(), 1.9);
    EXPECT_EQ(result.blue(), 1.9);
}

TEST(LightingTest, LightPointWithEyeAt45Degrees) {
    double value = std::sqrt(2.0) / 2.0;
    
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    auto eye = rtlib::create_vector(0.0, value, -value);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 0.0, -10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, false);
    EXPECT_EQ(result.red(), 1.0);
    EXPECT_EQ(result.green(), 1.0);
    EXPECT_EQ(result.blue(), 1.0);
}

TEST(LightingTest, LightPointWithLightAt45Degrees) {
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    
    auto eye = rtlib::create_vector(0.0, 0.0, -1.0);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 10.0, -10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, false);
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.red(), 0.736396));
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.green(), 0.736396));
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.blue(), 0.736396));
}

TEST(LightingTest, LightPointWithEyeAtLightReflection) {
    double value = std::sqrt(2.0) / 2.0;
    
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    
    auto eye = rtlib::create_vector(0.0, -value, -value);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 10.0, -10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, false);
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.red(), 1.6364));
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.green(), 1.6364));
    EXPECT_TRUE(rtlib::Tuple::doubleEquals(result.blue(), 1.6364));
}

TEST(LightingTest, LightPointWithLightBehindSurface) {
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    
    auto eye = rtlib::create_vector(0.0, 0.0, -1.0);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 0.0, 10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, false);
    EXPECT_EQ(result.red(), material._ambient);
    EXPECT_EQ(result.green(), material._ambient);
    EXPECT_EQ(result.blue(), material._ambient);
}

TEST(LightingTest, LightPointWithShadow) {
    rtlib::Material material;
    auto position = rtlib::create_point(0.0, 0.0, 0.0);
    
    auto eye = rtlib::create_vector(0.0, 0.0, -1.0);
    auto normal = rtlib::create_vector(0.0, 0.0, -1.0);
    
    auto lightOrigin = rtlib::create_point(0.0, 0.0, -10.0);
    auto intensity = rtlib::Colour(1.0, 1.0, 1.0);
    rtlib::Light light(lightOrigin, intensity);
    
    auto result = light.lightPoint(material, position, eye, normal, true);
    EXPECT_EQ(result.red(), material._ambient);
    EXPECT_EQ(result.green(), material._ambient);
    EXPECT_EQ(result.blue(), material._ambient);
}

}
