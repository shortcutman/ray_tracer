//
//  canvas.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 23/12/2022.
//

#ifndef canvas_hpp
#define canvas_hpp

#include "colour.hpp"
#include <vector>

namespace rtlib {

class Canvas {
public:
    typedef unsigned int PixelIndex;
    
private:
    PixelIndex _width;
    PixelIndex _height;
    std::vector<Colour> _canvas;
    
public:
    Canvas(PixelIndex width, PixelIndex height);
    ~Canvas() {}
    
    Colour pixel_at(PixelIndex x, PixelIndex y) const;
    void write_pixel(PixelIndex x, PixelIndex y, Colour colour);
    
    PixelIndex width() const;
    PixelIndex height() const;
};

}

#endif /* canvas_hpp */
