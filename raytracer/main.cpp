//
//  main.cpp
//  raytracer
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "camera.hpp"
#include "canvas.hpp"
#include "transformations.hpp"
#include "world.hpp"

#include <chrono>
#include <iostream>
#include <fstream>
#include <numbers>

using namespace rtlib;

int main(int argc, const char * argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto canvas = Canvas(1024, 1024);
    auto world = World::defaultWorld();
    auto camera = Camera(canvas.width(), canvas.height(), std::numbers::pi / 2.0);
    auto viewTransform = rtlib::viewTransform(create_point(0.0, 0.0, -5.0), create_point(0.0, 0.0, 0.0), create_vector(0.0, 1.0, 0.0));
    camera.setTransform(viewTransform);
    
    for (unsigned int x = 0; x < canvas.width(); x++) {
        for (unsigned int y = 0; y < canvas.height(); y++) {
            auto ray = camera.rayForPixel(x, y);
            auto colour = world.colourAt(ray);
            canvas.write_pixel(x, y, colour);
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Ray tracer duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    std::ofstream file;
    file.open("/tmp/out.ppm");
    
    if (!file.is_open()) {
        return 1;
    }
    
    file << canvas;
    file.close();
    
    return 0;
}
