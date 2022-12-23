//
//  canvas.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "canvas.hpp"

#include <cmath>
#include <ostream>

using namespace rtlib;

namespace {

unsigned int clampAndNormalize(double value) {
    auto clamped = std::clamp(value, 0.0, 1.0);
    auto normalized = std::round(clamped * 255);
    return normalized;
}

}

Canvas::Canvas(PixelIndex width, PixelIndex height) :
    _width(width),
    _height(height),
    _canvas(width * height)
{
}

Colour Canvas::pixel_at(PixelIndex x, PixelIndex y) const {
    if (x * y > _width * _height) {
        throw std::runtime_error("Pixel index is out of bounds.");
    }
    
    return _canvas[x * _width + y];
}

void Canvas::write_pixel(PixelIndex x, PixelIndex y, Colour colour) {
    if (x * y > _width * _height) {
        throw std::runtime_error("Pixel index is out of bounds.");
    }
    
    _canvas[x * _width + y] = colour;
}


Canvas::PixelIndex Canvas::width() const {
    return _width;
}

Canvas::PixelIndex Canvas::height() const {
    return _height;
}

 std::ostream& rtlib::operator<<(std::ostream& os, const Canvas& canvas) {
    os << "P3" << std::endl;
    os << canvas._width << " " << canvas._height << std::endl;
    os << "255" << std::endl;
     
     for (Canvas::PixelIndex y = 0; y < canvas._height; y++) {
         for (Canvas::PixelIndex x = 0; x < canvas._width; x++) {
             os << clampAndNormalize(canvas.pixel_at(x, y).red()) << " "
                << clampAndNormalize(canvas.pixel_at(x, y).green()) << " "
                << clampAndNormalize(canvas.pixel_at(x, y).blue()) << " ";
         }
         
         os << std::endl;
     }
     
     return os;
}
