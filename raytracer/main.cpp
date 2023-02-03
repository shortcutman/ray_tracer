//
//  main.cpp
//  raytracer
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "canvas.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "tuple.hpp"

#include <iostream>
#include <fstream>

using namespace rtlib;

int main(int argc, const char * argv[]) {
    
    auto viewOrigin = create_point(0.0, 0.0, -2.0);
    Sphere s;
    
    Canvas c(256, 256);
    for (unsigned int x = 0; x < c.width(); x++) {
        for (unsigned int y = 0; y < c.height(); y++) {
            double xRay = -1.0 + static_cast<double>(x) * (2.0 / 256.0);
            double yRay = -1.0 + static_cast<double>(y) * (2.0 / 256.0);
            
            Ray r(viewOrigin, create_vector(xRay, yRay, 1.0));
            auto hits = s.intersects(r);
            auto hit = rtlib::hit(hits);
            
            if (hit) {
                c.write_pixel(x, y, Colour(1.0, 0.0, 0.0));
            }
        }
    }
    
    std::ofstream file;
    file.open("/tmp/out.ppm");
    
    if (!file.is_open()) {
        return 1;
    }
    
    file << c;
    file.close();
    
    return 0;
}
