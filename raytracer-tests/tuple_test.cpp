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

TEST(TupleTest, CompareEqualPoints) {
    auto p1 = rtlib::create_point(4, -4, 3);
    auto p2 = rtlib::create_point(4, -4, 3);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TupleTest, CompareUnequalPoints) {
    auto p1 = rtlib::create_point(4, -4, 3);
    
    auto p2 = rtlib::create_point(1, -4, 3);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
    
    p2 = rtlib::create_point(4, -1, 3);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
    
    p2 = rtlib::create_point(4, -4, 1);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

TEST(TupleTest, CompareEqualVectors) {
    auto v1 = rtlib::create_vector(4, -4, 3);
    auto v2 = rtlib::create_vector(4, -4, 3);
    
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(TupleTest, CompareUnequalVectors) {
    auto v1 = rtlib::create_vector(4, -4, 3);
    
    auto v2 = rtlib::create_vector(1, -4, 3);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
    
    v2 = rtlib::create_vector(4, -1, 3);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
    
    v2 = rtlib::create_vector(4, -4, 1);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(TupleTest, ComparePointAndVector) {
    auto p1 = rtlib::create_point(4, -4, 3);
    auto v1 = rtlib::create_vector(4, -4, 3);
    
    EXPECT_FALSE(p1 == v1);
    EXPECT_TRUE(p1 != v1);
}

TEST(TupleTest, AddPoints) {
    auto p1 = rtlib::create_point(4, -4, 3);
    auto p2 = rtlib::create_point(4, -4, 3);
    auto p3 = p1 + p2;
    
    EXPECT_NE(p3, rtlib::create_point(8, -8, 6));
    EXPECT_NE(p3, rtlib::create_vector(8, -8, 6));
    EXPECT_TRUE(p3.w() == 2.0);
    EXPECT_FALSE(p3.isPoint());
    EXPECT_FALSE(p3.isVector());
}

TEST(TupleTest, AddVectors) {
    auto v1 = rtlib::create_vector(4, -4, 3);
    auto v2 = rtlib::create_vector(4, -4, 3);
    auto v3 = v1 + v2;
    
    EXPECT_EQ(v3, rtlib::create_vector(8, -8, 6));
    EXPECT_FALSE(v3.isPoint());
    EXPECT_TRUE(v3.isVector());
}

TEST(TupleTest, AddPointAndVector) {
    auto p1 = rtlib::create_point(3, -2, 5);
    auto v1 = rtlib::create_vector(-2, 3, 1);
    auto p2 = p1 + v1;
    
    EXPECT_EQ(p2, rtlib::create_point(1, 1, 6));
    EXPECT_TRUE(p2.isPoint());
    EXPECT_FALSE(p2.isVector());
}

TEST(TupleTest, SubtractPoints) {
    auto p1 = rtlib::create_point(3, 2, 1);
    auto p2 = rtlib::create_point(5, 6, 7);
    auto v1 = p1 - p2;
    
    EXPECT_EQ(v1, rtlib::create_vector(-2, -4, -6));
    EXPECT_FALSE(v1.isPoint());
    EXPECT_TRUE(v1.isVector());
}

TEST(TupleTest, SubtractVectors) {
    auto v1 = rtlib::create_vector(3, 2, 1);
    auto v2 = rtlib::create_vector(5, 6, 7);
    auto v3 = v1 - v2;
    
    EXPECT_EQ(v3, rtlib::create_vector(-2, -4, -6));
    EXPECT_FALSE(v3.isPoint());
    EXPECT_TRUE(v3.isVector());
}

TEST(TupleTest, SubtractPointFromVector) {
    auto v1 = rtlib::create_vector(3, 2, 1);
    auto p1 = rtlib::create_point(5, 6, 7);
    auto p2 = v1 - p1;
    
    EXPECT_NE(p2, rtlib::create_point(-2, -4, -6));
    EXPECT_NE(p2, rtlib::create_vector(-2, -4, -6));
    EXPECT_FALSE(p2.isPoint());
    EXPECT_FALSE(p2.isVector());
}

TEST(TupleTest, SubtractVectorFromPoint) {
    auto p1 = rtlib::create_point(3, 2, 1);
    auto v1 = rtlib::create_vector(5, 6, 7);
    auto p2 = p1 - v1;
    
    EXPECT_EQ(p2, rtlib::create_point(-2, -4, -6));
    EXPECT_TRUE(p2.isPoint());
    EXPECT_FALSE(p2.isVector());
}

TEST(TupleTest, NegateVector) {
    auto v1 = rtlib::create_vector(1, -2, 3);
    auto v2 = -v1;
    
    EXPECT_EQ(v2, rtlib::create_vector(-1, 2, -3));
    EXPECT_FALSE(v2.isPoint());
    EXPECT_TRUE(v2.isVector());
}

TEST(TupleTest, NegatePoint) {
    auto p1 = rtlib::create_point(1, -2, 3);
    auto p2 = -p1;
    
    EXPECT_NE(p2, rtlib::create_point(-1, 2, -3));
    EXPECT_FALSE(p2.isPoint());
    EXPECT_FALSE(p2.isVector());
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
