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

}
