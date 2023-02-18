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
#include <memory>
#include <numbers>

using namespace rtlib;

namespace {
World createWorld() {
    auto world = World();
    
    auto floor = std::make_shared<Sphere>();
    floor->setTransform(scaling(10, 0.01, 10));
    floor->material()._colour = Colour(1.0, 0.9, 0.9);
    floor->material()._specular = 0.0;
    world.addObject(floor);
    
    auto leftWall = std::make_shared<Sphere>();
    leftWall->setTransform(translation(0.0, 0.0, 5.0) *
                          rotation_y(-std::numbers::pi / 4.0) *
                          rotation_x(std::numbers::pi / 2.0) *
                          scaling(10.0, 0.01, 10.0));
    leftWall->setMaterial(floor->material());
    world.addObject(leftWall);
    
    auto rightWall = std::make_shared<Sphere>();
    rightWall->setTransform(translation(0.0, 0.0, 5.0) *
                          rotation_y(std::numbers::pi / 4.0) *
                          rotation_x(std::numbers::pi / 2.0) *
                          scaling(10.0, 0.01, 10.0));
    rightWall->setMaterial(floor->material());
    world.addObject(rightWall);
    
    auto middle = std::make_shared<Sphere>();
    middle->setTransform(translation(-0.5, 1.0, 0.5));
    middle->material()._colour = Colour(0.1, 1.0, 0.5);
    middle->material()._diffuse = 0.7;
    middle->material()._specular = 0.3;
    world.addObject(middle);
    
    auto right = std::make_shared<Sphere>();
    right->setTransform(translation(1.5, 0.5, -0.5) *
                       scaling(0.5, 0.5, 0.5));
    right->material()._colour = Colour(0.5, 1.0, 0.1);
    right->material()._diffuse = 0.7;
    right->material()._specular = 0.3;
    world.addObject(right);
    
    auto left = std::make_shared<Sphere>();
    left->setTransform(translation(-1.5, 0.33, -0.75) *
                        scaling(0.33, 0.33, 0.33));
    left->material()._colour = Colour(1.0, 0.8, 0.1);
    left->material()._diffuse = 0.7;
    left->material()._specular = 0.3;
    world.addObject(left);
    
    auto light = std::make_shared<Light>(create_point(-10, 10, -10), Colour(1.0, 1.0, 1.0));
    world.addLight(light);
    
    return world;
}

}

int main(int argc, const char * argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto canvas = Canvas(1000, 500);
    auto world = createWorld();
    auto camera = Camera(canvas.width(), canvas.height(), std::numbers::pi / 3.0);
    auto viewTransform = rtlib::viewTransform(create_point(0.0, 1.5, -5.0), create_point(0.0, 1.0, 0.0), create_vector(0.0, 1.0, 0.0));
    camera.setTransform(viewTransform);
    
    for (unsigned int x = 0; x < canvas.width(); x++) {
        for (unsigned int y = 0; y < canvas.height(); y++) {
            auto ray = camera.rayForPixel(x, y);
            auto colour = world.colourAt(ray);
            canvas.writePixel(x, y, colour);
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
