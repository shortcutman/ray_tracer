//
//  main.cpp
//  raytracer
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "camera.hpp"
#include "canvas.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "transformations.hpp"
#include "world.hpp"

#include "oneapi/tbb.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>
#include <numbers>

using namespace rtlib;

namespace {
std::unique_ptr<World> createWorld() {
    auto world = std::make_unique<World>();
    
    auto floor = std::make_unique<Plane>();
    floor->material()._colour = Colour(1.0, 0.9, 0.9);
    floor->material()._specular = 0.0;
    floor->material()._reflective = 0.5;
    world->addObject(std::move(floor));

    auto leftWall = std::make_unique<Plane>();
    leftWall->setTransform(translation(0.0, 0.0, 5.0) *
                          rotation_y(-std::numbers::pi / 4.0) *
                          rotation_x(std::numbers::pi / 2.0));
    leftWall->material()._colour = Colour(1.0, 0.9, 0.9);
    leftWall->material()._specular = 0.0;
    leftWall->material()._reflective = 0.5;
    world->addObject(std::move(leftWall));

    auto rightWall = std::make_unique<Plane>();
    rightWall->setTransform(translation(0.0, 0.0, 5.0) *
                            rotation_y(std::numbers::pi / 4.0) *
                            rotation_x(std::numbers::pi / 2.0));
    rightWall->material()._colour = Colour(0.0, 0.3, 0.9);
    rightWall->material()._specular = 0.0;
    world->addObject(std::move(rightWall));

    auto white = Colour(1.0, 1.0, 1.0);
    auto black = Colour(0.0, 0.0, 0.0);

    auto middle = std::make_unique<Sphere>();
    middle->setTransform(translation(-0.5, 1.0, 0.5));
    middle->material()._pattern = std::make_shared<StripePattern>(white, black);
    middle->material()._pattern->setTransform(scaling(0.1, 0.1, 0.1));
    middle->material()._colour = Colour(0.1, 1.0, 0.5);
    middle->material()._diffuse = 0.7;
    middle->material()._specular = 0.3;
    world->addObject(std::move(middle));
    
    auto right = std::make_unique<Sphere>();
    right->setTransform(translation(1.5, 0.5, -0.5) *
                       scaling(0.5, 0.5, 0.5));
    right->material()._colour = Colour(0.5, 1.0, 0.1);
    right->material()._diffuse = 0.7;
    right->material()._specular = 0.3;
    world->addObject(std::move(right));
    
    auto left = std::make_unique<Sphere>();
    left->setTransform(translation(-1.5, 0.33, -0.75) *
                        scaling(0.33, 0.33, 0.33));
    left->material()._colour = Colour(1.0, 0.8, 0.1);
    left->material()._diffuse = 0.7;
    left->material()._specular = 0.3;
    world->addObject(std::move(left));
    
    auto light = std::make_unique<Light>(create_point(-10, 10, -10), Colour(1.0, 1.0, 1.0));
    world->addLight(std::move(light));
    
    return world;
}

void runFuncTimed(std::function<void(void)> func) {
    auto start = std::chrono::high_resolution_clock::now();
    
    func();
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Ray tracer duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}

void renderSingleThreaded(Canvas& canvas, const Camera& camera, const World& world) {
    for (unsigned int x = 0; x < canvas.width(); x++) {
        for (unsigned int y = 0; y < canvas.height(); y++) {
            auto ray = camera.rayForPixel(x, y);
            auto colour = world.colourAt(ray);
            canvas.writePixel(x, y, colour);
        }
    }
}

struct ScanLine {
    unsigned int yStart;
    unsigned int yEnd;
    unsigned int width;
    std::chrono::milliseconds clock;
};

void renderMultiThreaded(Canvas& canvas, const Camera& camera, const World& world) {
    unsigned int y = 0;
    
    oneapi::tbb::parallel_pipeline(6,
        oneapi::tbb::make_filter<void, ScanLine>(oneapi::tbb::filter_mode::serial_in_order, [&y, &canvas, &camera, &world] (oneapi::tbb::flow_control& fc) -> ScanLine {
            if (y < canvas.height()) {
                ScanLine s;
                s.yStart = y;
                y += canvas.height() / 10;
                s.yEnd = y;
                s.width = canvas.width();
                return s;
            }
                
            fc.stop();
            return ScanLine();
        }) &
        oneapi::tbb::make_filter<ScanLine, ScanLine>(oneapi::tbb::filter_mode::parallel, [&canvas, &camera, &world] (ScanLine s) -> ScanLine {
            auto start = std::chrono::high_resolution_clock::now();
            for (unsigned int y = s.yStart; y < s.yEnd; y++) {
                for (unsigned int x = 0; x < s.width; x++) {
                    auto ray = camera.rayForPixel(x, y);
                    auto colour = world.colourAt(ray);
                    canvas.writePixel(x, y, colour);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            s.clock = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            return s;
        }) &
        oneapi::tbb::make_filter<ScanLine, void>(oneapi::tbb::filter_mode::serial_in_order, [] (ScanLine s) {
            std::cout << "Scan line yStart: " << s.yStart << " time: " << s.clock.count() << std::endl;
        }));
}

}

int main(int argc, const char * argv[]) {
    auto canvas = Canvas(1000, 500);
    auto world = createWorld();
    auto camera = Camera(canvas.width(), canvas.height(), std::numbers::pi / 3.0);
    auto viewTransform = rtlib::viewTransform(create_point(0.0, 1.5, -5.0), create_point(0.0, 1.0, 0.0), create_vector(0.0, 1.0, 0.0));
    camera.setTransform(viewTransform);
    
    std::cout << "Single thread" << std::endl;
    runFuncTimed([&] () {
        renderSingleThreaded(canvas, camera, *world);
    });

    std::cout << "Multi thread" << std::endl;
    runFuncTimed([&] () {
        renderMultiThreaded(canvas, camera, *world);
    });
    
    std::ofstream file;
    file.open("/tmp/out.ppm");
    
    if (!file.is_open()) {
        return 1;
    }
    
    file << canvas;
    file.close();
    
    return 0;
}
