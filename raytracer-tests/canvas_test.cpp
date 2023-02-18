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
            EXPECT_EQ(c.pixelAt(x, y), baseColour)
            << "Location x: " << x << " y: " << y;
        }
    }
}

TEST(CanvasTest, WriteToCanvas) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    rtlib::Colour colour(0.3, 0.4, 0.5);
    
    c.writePixel(2, 3, colour);
    EXPECT_EQ(c.pixelAt(2, 3), colour);
    EXPECT_EQ(c.pixelAt(2, 4), rtlib::Colour());
    EXPECT_EQ(c.pixelAt(3, 2), rtlib::Colour());
}

TEST(CanvasTest, WriteToCanvasAspect) {
    rtlib::Canvas c(20, 10);
    
    EXPECT_EQ(c.width(), 20);
    EXPECT_EQ(c.height(), 10);
    
    rtlib::Colour colour(0.3, 0.4, 0.5);
    
    c.writePixel(10, 3, colour);
    EXPECT_EQ(c.pixelAt(10, 3), colour);
    EXPECT_EQ(c.pixelAt(10, 4), rtlib::Colour());
    EXPECT_EQ(c.pixelAt(10, 2), rtlib::Colour());
}

TEST(CanvasTest, ErrorOnReadPixelOutOfBounds) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    EXPECT_THROW(c.pixelAt(11, 20), std::runtime_error);
}

TEST(CanvasTest, ErrorOnWritePixelOutOfBounds) {
    rtlib::Canvas c(10, 20);
    
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    
    EXPECT_THROW(c.writePixel(11, 20, rtlib::Colour(0.2, 0.0, 0.0)), std::runtime_error);
}

TEST(CanvasTest, WriteOutPPMHeader) {
    rtlib::Canvas c(5, 3);
    
    std::stringstream ss;
    ss << c;
    
    std::string magicWord;
    std::getline(ss, magicWord);
    EXPECT_EQ(magicWord, "P3");
    
    std::string size;
    std::getline(ss, size);
    EXPECT_EQ(size, "5 3");
    
    std::string maxColourValue;
    std::getline(ss, maxColourValue);
    EXPECT_EQ(maxColourValue, "255");
}

TEST(CanvasTest, WriteOutPPMPixels) {
    rtlib::Canvas c(5, 3);
    c.writePixel(0, 0, rtlib::Colour(1.5, 0.0, 0.0));
    c.writePixel(2, 1, rtlib::Colour(0.0, 0.5, 0.0));
    c.writePixel(4, 2, rtlib::Colour(-0.5, 0.0, 1.0));
    
    std::stringstream ss;
    ss << c;
    
    std::string line;
    std::getline(ss, line);
    EXPECT_EQ(line, "P3");
    std::getline(ss, line);
    EXPECT_EQ(line, "5 3");
    std::getline(ss, line);
    EXPECT_EQ(line, "255");
    std::getline(ss, line);
    EXPECT_EQ(line, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ") << "Row 1";
    std::getline(ss, line);
    EXPECT_EQ(line, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 ") << "Row 2";
    std::getline(ss, line);
    EXPECT_EQ(line, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 ") << "Row 3";
}

}
