//
//  world_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 12/2/2023.
//

#include <gtest/gtest.h>

#include "ray.hpp"
#include "world.hpp"

using namespace rtlib;

namespace {

TEST(WorldTest, EmptyWorld) {
    World w;
    EXPECT_EQ(w.lights().size(), 0);
    EXPECT_EQ(w.objects().size(), 0);
}

TEST(WorldTest, IntersectWorld) {
    World w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    
    auto hits = w.intersects(r);
    
    EXPECT_EQ(hits.size(), 4);
    EXPECT_EQ(hits[0].t, 4);
    EXPECT_EQ(hits[1].t, 4.5);
    EXPECT_EQ(hits[2].t, 5.5);
    EXPECT_EQ(hits[3].t, 6);
}

TEST(WorldTest, ShadeIntersectsFromOutside) {
    World w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto shape = w.objects().front();
    auto hits = w.intersects(r);
    auto values = IntersectValues(hits.front(), r);
    auto colour = w.shadeHits(values);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadeIntersectsFromInside) {
    World w = rtlib::World::defaultWorld();
    w.lights().front() = std::make_shared<Light>(create_point(0.0, 0.25, 0.0), Colour(1.0, 1.0, 1.0));
    Ray r(create_point(0.0, 0.0, 0.0), create_vector(0.0, 0.0, 1.0));
    auto shape = w.objects().front();
    auto hits = w.intersects(r);
    auto values = IntersectValues(hits.front(), r);
    auto colour = w.shadeHits(values);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColourAtRayMiss) {
    World w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 1.0, 0.0));
    auto colour = w.colourAt(r);
    
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, ColourAtRayHit) {
    World w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto colour = w.colourAt(r);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColourAtRayInside) {
    World w = rtlib::World::defaultWorld();
    w.objects().front()->material()._ambient = 1.0;
    w.objects().back()->material()._ambient = 1.0;
    
    Ray r(create_point(0.0, 0.0, 0.75), create_vector(0.0, 0.0, -1.0));
    auto colour = w.colourAt(r);
    
    EXPECT_EQ(colour, w.objects().back()->material()._colour);
}



}
