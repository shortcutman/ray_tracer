//
//  tuple_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 18/12/2022.
//

#include <gtest/gtest.h>

#include "tuple.hpp"

namespace {

TEST(TupleTest, ConstructPointFromTuple) {
    rtlib::Tuple t(4.3, -4.2, 3.1, 1.0);
    
    EXPECT_EQ(t.x(), 4.3);
    EXPECT_EQ(t.y(), -4.2);
    EXPECT_EQ(t.z(), 3.1);
    EXPECT_EQ(t.w(), 1.0);
    
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TupleTest, ConstructVectorFromTuple) {
    rtlib::Tuple t(4.3, -4.2, 3.1, 0.0);
    
    EXPECT_EQ(t.x(), 4.3);
    EXPECT_EQ(t.y(), -4.2);
    EXPECT_EQ(t.z(), 3.1);
    EXPECT_EQ(t.w(), 0.0);
    
    EXPECT_FALSE(t.isPoint());
    EXPECT_TRUE(t.isVector());
}

TEST(TupleTest, ConstructPointByName) {
    auto p = rtlib::create_point(4, -4, 3);
    
    EXPECT_EQ(p.x(), 4.);
    EXPECT_EQ(p.y(), -4.);
    EXPECT_EQ(p.z(), 3.);
    EXPECT_EQ(p.w(), 1.0);
    
    EXPECT_TRUE(p.isPoint());
    EXPECT_FALSE(p.isVector());
}

TEST(TupleTest, ConstructVectorByName) {
    auto v = rtlib::create_vector(4, -4, 3);
    
    EXPECT_EQ(v.x(), 4.);
    EXPECT_EQ(v.y(), -4.);
    EXPECT_EQ(v.z(), 3.);
    EXPECT_EQ(v.w(), 0.0);
    
    EXPECT_FALSE(v.isPoint());
    EXPECT_TRUE(v.isVector());
}

}
