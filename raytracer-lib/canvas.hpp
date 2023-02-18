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
    
    Colour pixelAt(PixelIndex x, PixelIndex y) const;
    void writePixel(PixelIndex x, PixelIndex y, Colour colour);
    
    PixelIndex width() const;
    PixelIndex height() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas);
};

}

#endif /* canvas_hpp */
