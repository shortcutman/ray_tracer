//
//  tuple_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 18/12/2022.
//

#include <gtest/gtest.h>

#include "tuple.hpp"

namespace {

TEST(TupleTest, ConstructPoint) {
    rtlib::Tuple t(4.3f, -4.2f, 3.1f, 1.0f);
    
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 1.0f);
    
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TupleTest, ConstructVector) {
    rtlib::Tuple t(4.3f, -4.2f, 3.1f, 0.0f);
    
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 0.0f);
    
    EXPECT_FALSE(t.isPoint());
    EXPECT_TRUE(t.isVector());
}

}
