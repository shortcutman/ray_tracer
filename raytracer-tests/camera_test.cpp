//
//  camera_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 17/2/2023.
//

#include <gtest/gtest.h>

#include "camera.hpp"
#include "transformations.hpp"

#include <cmath>
#include <numbers>

namespace {

TEST(CameraTest, ConstructCamera) {
    rtlib::Camera camera(160, 120, std::numbers::pi / 2.0);
    
    EXPECT_EQ(camera.horizontalSize(), 160);
    EXPECT_EQ(camera.verticalSize(), 120);
    EXPECT_EQ(camera.fieldOfView(), std::numbers::pi / 2.0);
    EXPECT_EQ(camera.transform(), rtlib::Matrix4x4::identityMatrix());
}

TEST(CameraTest, PixelSizeForHorizontalCanvas) {
    rtlib::Camera camera(200, 125, std::numbers::pi / 2.0);
    
    EXPECT_DOUBLE_EQ(camera.pixelSize(), 0.01);
}

TEST(CameraTest, PixelSizeForVerticalCanvas) {
    rtlib::Camera camera(125, 200, std::numbers::pi / 2.0);
    
    EXPECT_DOUBLE_EQ(camera.pixelSize(), 0.01);
}

TEST(CameraTest, RayThroughCentreOfCanvas) {
    rtlib::Camera camera(201, 101, std::numbers::pi / 2.0);
    auto ray = camera.rayForPixel(100, 50);
    EXPECT_EQ(ray.origin(), rtlib::create_point(0.0, 0.0, 0.0));
    EXPECT_EQ(ray.direction(), rtlib::create_vector(0.0, 0.0, -1.0));
}

TEST(CameraTest, RayThroughCornerOfCanvas) {
    rtlib::Camera camera(201, 101, std::numbers::pi / 2.0);
    auto ray = camera.rayForPixel(0, 0);
    EXPECT_EQ(ray.origin(), rtlib::create_point(0.0, 0.0, 0.0));
    EXPECT_EQ(ray.direction(), rtlib::create_vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayOnTransformedCamera) {
    rtlib::Camera camera(201, 101, std::numbers::pi / 2.0);
    camera.setTransform(rtlib::rotation_y(std::numbers::pi / 4.0) * rtlib::translation(0.0, -2.0, 5.0));
    auto ray = camera.rayForPixel(100, 50);
    EXPECT_EQ(ray.origin(), rtlib::create_point(0.0, 2.0, -5.0));
    EXPECT_EQ(ray.direction(), rtlib::create_vector(std::sqrt(2.0) / 2.0, 0.0, -std::sqrt(2.0) / 2.0));
}


}
