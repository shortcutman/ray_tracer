//
//  canvas_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 23/12/2022.
//

#include <gtest/gtest.h>

#include "canvas.hpp"

namespace {

TEST(CanvasTest, CreateCanvas) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    rtlib::Colour baseColour(0.0, 0.0, 0.0);
    
    for (rtlib::Canvas::PixelIndex x = 0; x < 10; x++) {
        for (rtlib::Canvas::PixelIndex y = 0; y < 10; y++) {
            EXPECT_EQ(c.pixel_at(x, y), baseColour)
            << "Location x: " << x << " y: " << y;
        }
    }
}

TEST(CanvasTest, WriteToCanvas) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    rtlib::Colour colour(0.3, 0.4, 0.5);
    
    c.write_pixel(2, 3, colour);
    EXPECT_EQ(c.pixel_at(2, 3), colour);
    EXPECT_EQ(c.pixel_at(2, 4), rtlib::Colour());
    EXPECT_EQ(c.pixel_at(3, 2), rtlib::Colour());
}

TEST(CanvasTest, ErrorOnReadPixelOutOfBounds) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    EXPECT_THROW(c.pixel_at(11, 20), std::runtime_error);
}

TEST(CanvasTest, ErrorOnWritePixelOutOfBounds) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    EXPECT_THROW(c.write_pixel(11, 20, rtlib::Colour(0.2, 0.0, 0.0)), std::runtime_error);
}

}
