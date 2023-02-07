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

#include <chrono>
#include <iostream>
#include <fstream>

using namespace rtlib;

int main(int argc, const char * argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto viewOrigin = create_point(0.0, 0.0, -2.0);
    Light light(create_point(-10.0, 10.0, -10.0), Colour(1.0, 1.0, 1.0));
    Sphere s;
    auto m = s.material();
    m._colour = Colour(1.0, 0.2, 1.0);
    s.setMaterial(m);
    
    Canvas c(1024, 1024);
    for (unsigned int x = 0; x < c.width(); x++) {
        for (unsigned int y = 0; y < c.height(); y++) {
            double xRay = -1.0 + static_cast<double>(x) * (2.0 / c.width());
            double yRay = -1.0 + static_cast<double>(y) * (2.0 / c.height());
            
            Ray r(viewOrigin, create_vector(xRay, yRay, 1.0));
            auto hits = s.intersects(r);
            auto hit = rtlib::hit(hits);
            
            if (hit) {
                auto hitPoint = r.positionAt(hit->t);
                auto litColour = light.lightPoint(s.material(),
                                                  hitPoint,
                                                  -r.direction().normalised(),
                                                  s.normalAt(hitPoint));
                c.write_pixel(x, y, litColour);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Ray tracer duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    std::ofstream file;
    file.open("/tmp/out.ppm");
    
    if (!file.is_open()) {
        return 1;
    }
    
    file << c;
    file.close();
    
    return 0;
}
