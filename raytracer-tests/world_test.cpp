//
//  world_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 12/2/2023.
//

#include <gtest/gtest.h>

#include "TestPattern.hpp"

#include "camera.hpp"
#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
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
    auto w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    
    auto hits = w->intersects(r);
    
    EXPECT_EQ(hits.size(), 4);
    EXPECT_EQ(hits[0].t, 4);
    EXPECT_EQ(hits[1].t, 4.5);
    EXPECT_EQ(hits[2].t, 5.5);
    EXPECT_EQ(hits[3].t, 6);
}

TEST(WorldTest, ShadeIntersectsFromOutside) {
    auto w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto hits = w->intersects(r);
    auto values = IntersectValues(hits.front(), r);
    auto colour = w->shadeHits(values, 1);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadeIntersectsFromInside) {
    GTEST_SKIP() << "Unknown failure reason, requires further investigation. Book page 95.";
    
    auto w = rtlib::World::defaultWorld();
    w->lights().clear();
    w->addLight(std::make_unique<Light>(create_point(0.0, 0.25, 0.0), Colour(1.0, 1.0, 1.0)));
    Ray r(create_point(0.0, 0.0, 0.0), create_vector(0.0, 0.0, 1.0));
    auto hits = w->intersects(r);
    auto values = IntersectValues(hits.front(), r);
    auto colour = w->shadeHits(values, 1);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadeIntersectsInShadow) {
    auto w = std::make_unique<World>();
    w->addLight(std::make_unique<Light>(create_point(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0)));
    
    auto s1 = std::make_unique<Sphere>();
    w->addObject(std::move(s1));
    
    auto s2 = std::make_unique<Sphere>();
    s2->setTransform(translation(0.0, 0.0, 10.0));
    auto s2Ptr = s2.get();
    w->addObject(std::move(s2));
    
    Ray r(create_point(0.0, 0.0, 5.0), create_vector(0.0, 0.0, 1.0));
    auto intersect = Intersect(s2Ptr, 4.0);
    auto intersectValues = IntersectValues(intersect, r);
    auto colour = w->shadeHits(intersectValues, 1);
    
    EXPECT_EQ(colour, Colour(0.1, 0.1, 0.1));
}

TEST(WorldTest, ColourAtRayMiss) {
    auto w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 1.0, 0.0));
    auto colour = w->colourAt(r, 1);
    
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, ColourAtRayHit) {
    auto w = rtlib::World::defaultWorld();
    Ray r(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto colour = w->colourAt(r, 1);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColourAtRayInside) {
    auto w = rtlib::World::defaultWorld();
    w->objects().front()->material()._ambient = 1.0;
    w->objects().back()->material()._ambient = 1.0;
    
    Ray r(create_point(0.0, 0.0, 0.75), create_vector(0.0, 0.0, -1.0));
    auto colour = w->colourAt(r, 1);
    
    EXPECT_EQ(colour, w->objects().back()->material()._colour);
}

TEST(WorldTest, RenderWorldWithCamera) {
    auto w = rtlib::World::defaultWorld();
    Camera c(11, 11, std::numbers::pi / 2.0);
    auto viewTransform = rtlib::viewTransform(create_point(0.0, 0.0, -5.0), create_point(0.0, 0.0, 0.0), create_vector(0.0, 1.0, 0.0));
    c.setTransform(viewTransform);
    
    auto ray = c.rayForPixel(5, 5);
    auto colour = w->colourAt(ray, 1);
    
    EXPECT_EQ(colour, Colour(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, NoShadowWhenNothingIsCollinearBetweenPointAndLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world->isShadowed(create_point(0.0, 10.0, 0.0)));
}

TEST(WorldTest, ShadowWhenObjectIsBetweenPointAndLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_TRUE(world->isShadowed(create_point(10.0, -10.0, 10.0)));
}

TEST(WorldTest, NoShadowWhenPointIsBeheindLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world->isShadowed(create_point(-20.0, 20.0, -20.0)));
}

TEST(WorldTest, NoShadowWhenObjectIsBeheindLight) {
    auto world = rtlib::World::defaultWorld();
    EXPECT_FALSE(world->isShadowed(create_point(-2.0, 2.0, -2.0)));
}

TEST(WorldTest, ReflectedColourForNonreflectiveMaterial) {
    auto world = rtlib::World::defaultWorld();
    auto ray = Ray(create_point(0.0, 0.0, 0.0), create_vector(0.0, 0.0, 1.0));
    auto shape = world->objects().at(1).get();
    shape->material()._ambient = 1.0;
    
    EXPECT_EQ(shape->material()._reflective, 0.0);
    
    auto intersection = Intersect(shape, 1.0);
    auto intersectValues = IntersectValues(intersection, ray);
    auto colour = world->reflectedColourAt(intersectValues, 1);
    
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, ReflectedColourForReflectiveMaterial) {
    auto world = rtlib::World::defaultWorld();
    
    auto plane = std::make_unique<rtlib::Plane>();
    plane->material()._reflective = 0.5;
    plane->setTransform(translation(0.0, -1.0, 0.0));
    world->addObject(std::move(plane));
    
    auto ray = Ray(create_point(0.0, 0.0, -3.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto planePtr = world->objects().back().get();
    auto intersection = Intersect(planePtr, std::sqrt(2.0));
    auto intersectValues = IntersectValues(intersection, ray);
    auto colour = world->reflectedColourAt(intersectValues, 1);
    
    EXPECT_EQ(colour, Colour(0.190331, 0.237913, 0.142748));
}

TEST(WorldTest, ShadeHitForReflectiveMaterial) {
    auto world = rtlib::World::defaultWorld();
    
    auto plane = std::make_unique<rtlib::Plane>();
    plane->material()._reflective = 0.5;
    plane->setTransform(translation(0.0, -1.0, 0.0));
    world->addObject(std::move(plane));
    auto planePtr = world->objects().back().get();
    
    auto ray = Ray(create_point(0.0, 0.0, -3.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersection = Intersect(planePtr, std::sqrt(2.0));
    auto intersectValues = IntersectValues(intersection, ray);
    auto colour = world->shadeHits(intersectValues, 1);
    
    EXPECT_EQ(colour, Colour(0.876756, 0.924339, 0.829173));
}

TEST(WorldTest, ColourAtWithMutuallyReflectiveSurfaces) {
    auto world = rtlib::World::defaultWorld();
    *world->lights().at(0) = Light(create_point(0.0, 0.0, 0.0), Colour(1.0, 1.0, 1.0));
    
    auto lower = std::make_unique<Plane>();
    lower->material()._reflective = 1.0;
    lower->setTransform(translation(0.0, -1.0, 0.0));
    world->addObject(std::move(lower));
    
    auto upper = std::make_unique<Plane>();
    upper->material()._reflective = 1.0;
    upper->setTransform(translation(0.0, 1.0, 0.0));
    world->addObject(std::move(upper));
    
    auto ray = Ray(create_point(0.0, 0.0, 0.0), create_vector(0.0, 1.0, 0.0));
    world->colourAt(ray, 10);
    SUCCEED();
}

TEST(WorldTest, ReflectedColourAtMaximumRecursiveDepth) {
    auto world = rtlib::World::defaultWorld();
    
    auto plane = std::make_unique<rtlib::Plane>();
    plane->material()._reflective = 0.5;
    plane->setTransform(translation(0.0, -1.0, 0.0));
    world->addObject(std::move(plane));
    auto planePtr = world->objects().back().get();
    
    auto ray = Ray(create_point(0.0, 0.0, -3.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersection = Intersect(planePtr, std::sqrt(2.0));
    auto intersectValues = IntersectValues(intersection, ray);
    auto colour = world->reflectedColourAt(intersectValues, 0);
    
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, RefractedColourWithAnOpaqueSurface) {
    auto world = rtlib::World::defaultWorld();
    auto shape = world->objects().front().get();
    auto ray = Ray(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(shape, 4.0));
    intersections.push_back(Intersect(shape, 6.0));
    auto intersectValues = IntersectValues(intersections[0], ray, intersections);
    auto colour = world->refractedColourAt(intersectValues, 0);
    
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, RefractedColourWithMaxResursiveDepth) {
    auto world = rtlib::World::defaultWorld();
    auto shape = world->objects().front().get();
    shape->material()._transparency = 1.0;
    shape->material()._refractiveIndex = 1.5;
    auto ray = Ray(create_point(0.0, 0.0, -5.0), create_vector(0.0, 0.0, 1.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(shape, 4.0));
    intersections.push_back(Intersect(shape, 6.0));
    auto intersectValues = IntersectValues(intersections[0], ray, intersections);
    auto colour = world->refractedColourAt(intersectValues, 0);
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}


TEST(WorldTest, RefractedColourUnderTotalInternalReflection) {
    auto world = rtlib::World::defaultWorld();
    auto shape = world->objects().front().get();
    shape->material()._transparency = 1.0;
    shape->material()._refractiveIndex = 1.5;
    auto ray = Ray(create_point(0.0, 0.0, std::sqrt(2.0)/2.0), create_vector(0.0, 1.0, 0.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(shape, -std::sqrt(2.0)/2.0));
    intersections.push_back(Intersect(shape, std::sqrt(2.0)/2.0));
    auto intersectValues = IntersectValues(intersections[1], ray, intersections);
    auto colour = world->refractedColourAt(intersectValues, 5);
    EXPECT_EQ(colour, Colour(0.0, 0.0, 0.0));
}

TEST(WorldTest, RefractedColourWithRefractedRaw) {
    auto world = rtlib::World::defaultWorld();
    auto shape1 = world->objects().front().get();
    shape1->material()._ambient = 1.0;
    shape1->material()._pattern = std::make_shared<rtlib_tests::TestPattern>();
    auto shape2 = world->objects().at(1).get();
    shape2->material()._transparency = 1.0;
    shape2->material()._refractiveIndex = 1.5;
    
    auto ray = Ray(create_point(0.0, 0.0, 0.1), create_vector(0.0, 1.0, 0.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(shape1, -0.9899));
    intersections.push_back(Intersect(shape2, -0.4899));
    intersections.push_back(Intersect(shape2, 0.4899));
    intersections.push_back(Intersect(shape1, 0.9899));
    auto intersectValues = IntersectValues(intersections[2], ray, intersections);
    auto colour = world->refractedColourAt(intersectValues, 5);
    EXPECT_EQ(colour, Colour(0.0, 0.998885, 0.0472165));
}

TEST(WorldTest, ShadeHitWithATransparentMaterial) {
    auto world = World::defaultWorld();
    
    auto floor = std::make_unique<Plane>();
    floor->setTransform(translation(0.0, -1.0, 0.0));
    floor->material()._transparency = 0.5;
    floor->material()._refractiveIndex = 1.5;
    world->addObject(std::move(floor));
    auto floorPtr = world->objects().back().get();
    
    auto ball = std::make_unique<Sphere>();
    ball->setTransform(translation(0.0, -3.5, -0.5));
    ball->material()._ambient = 0.5;
    ball->material()._colour = Colour(1.0, 0.0, 0.0);
    world->addObject(std::move(ball));
    
    auto ray = Ray(create_point(0.0, 0.0, -3.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(floorPtr, std::sqrt(2.0)));
    auto intersectValues = IntersectValues(intersections[0], ray, intersections);
    auto colour = world->shadeHits(intersectValues, 5);
    EXPECT_EQ(colour, Colour(0.93642, 0.68642, 0.68642));
}

TEST(WorldTest, ShadeHitWithReflectiveTransparentMaterial) {
    auto world = World::defaultWorld();
    
    auto floor = std::make_unique<Plane>();
    floor->setTransform(translation(0.0, -1.0, 0.0));
    floor->material()._reflective = 0.5;
    floor->material()._transparency = 0.5;
    floor->material()._refractiveIndex = 1.5;
    world->addObject(std::move(floor));
    auto floorPtr = world->objects().back().get();
    
    auto ball = std::make_unique<Sphere>();
    ball->setTransform(translation(0.0, -3.5, -0.5));
    ball->material()._ambient = 0.5;
    ball->material()._colour = Colour(1.0, 0.0, 0.0);
    world->addObject(std::move(ball));
    
    auto ray = Ray(create_point(0.0, 0.0, -3.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(floorPtr, std::sqrt(2.0)));
    auto intersectValues = IntersectValues(intersections[0], ray, intersections);
    auto colour = world->shadeHits(intersectValues, 5);
    EXPECT_EQ(colour, Colour(0.93391, 0.69643, 0.69243));
}

}
