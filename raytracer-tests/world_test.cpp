//
//  world_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 12/2/2023.
//

#include <gtest/gtest.h>

#include "camera.hpp"
#include "ray.hpp"
#include "transformations.hpp"
#include "world.hpp"

#include <numbers>

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

TEST(WorldTest, ShadeIntersectsInShadow) {
    auto w = World();
    w.addLight(std::make_shared<Light>(create_point(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0)));
    auto s1 = std::make_shared<Sphere>();
    w.addObject(s1);
    auto s2 = std::make_shared<Sphere>();
    s2->setTransform(translation(0.0, 0.0, 10.0));
    w.addObject(s2);
    
    Ray r(create_point(0.0, 0.0, 5.0), create_vector(0.0, 0.0, 1.0));
    auto intersect = Intersect(s2.get(), 4.0);
    auto intersectValues = IntersectValues(intersect, r);
    auto colour = w.shadeHits(intersectValues);
    
    EXPECT_EQ(colour, Colour(0.1, 0.1, 0.1));
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

TEST(WorldTest, RenderWorldWithCamera) {
    World w = rtlib::World::defaultWorld();
    Camera c(11, 11, std::numbers::pi / 2.0);
    auto viewTransform = rtlib::viewTransform(create_point(0.0, 0.0, -5.0), create_point(0.0, 0.0, 0.0), create_vector(0.0, 1.0, 0.0));
    c.setTransform(viewTransform);
    
    auto ray = c.rayForPixel(5, 5);
    auto colour = w.colourAt(ray);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, NoShadowWhenNothingIsCollinearBetweenPointAndLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world.isShadowed(create_point(0.0, 10.0, 0.0)));
}

TEST(WorldTest, ShadowWhenObjectIsBetweenPointAndLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_TRUE(world.isShadowed(create_point(10.0, -10.0, 10.0)));
}

TEST(WorldTest, NoShadowWhenPointIsBeheindLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world.isShadowed(create_point(-20.0, 20.0, -20.0)));
}

TEST(WorldTest, NoShadowWhenObjectIsBeheindLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world.isShadowed(create_point(-2.0, 2.0, -2.0)));
}

}
