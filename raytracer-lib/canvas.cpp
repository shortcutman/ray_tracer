//
//  canvas.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#include "canvas.hpp"

using namespace rtlib;

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
    
    return _canvas[x * y];
}

void Canvas::write_pixel(PixelIndex x, PixelIndex y, Colour colour) {
    if (x * y > _width * _height) {
        throw std::runtime_error("Pixel index is out of bounds.");
    }
    
    _canvas[x * y] = colour;
}


Canvas::PixelIndex Canvas::width() const {
    return _width;
}

Canvas::PixelIndex Canvas::height() const {
    return _height;
}
