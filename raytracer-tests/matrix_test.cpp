//
//  matrix_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 23/12/2022.
//

#include <gtest/gtest.h>

#include "matrix.hpp"

namespace {

TEST(MatrixTest, ConstructMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {1.0, 2.0, 3.0, 4.0},
        {5.5, 6.5, 7.5, 8.5},
        {9.0, 10.0, 11.0, 12.0},
        {13.5, 14.5, 15.5, 16.5}
    }});
    
    EXPECT_EQ(m.at(0, 0), 1);
    EXPECT_EQ(m.at(0, 3), 4);
    EXPECT_EQ(m.at(1, 0), 5.5);
    EXPECT_EQ(m.at(1, 2), 7.5);
    EXPECT_EQ(m.at(2, 2), 11);
    EXPECT_EQ(m.at(3, 0), 13.5);
    EXPECT_EQ(m.at(3, 2), 15.5);
}

TEST(MatrixTest, ConstructMatrix3x3) {
    rtlib::Matrix3x3 m({{
        {-3.0, 5.0, 0.0},
        {1.0, -2.0, -7.0},
        {0.0, 1.0, 1.0}
    }});
    
    EXPECT_EQ(m.at(0, 0), -3);
    EXPECT_EQ(m.at(1, 1), -2);
    EXPECT_EQ(m.at(2, 2), 1);
}

TEST(MatrixTest, ConstructMatrix2x2) {
    rtlib::Matrix4x4 m({{
        {-3.0, 5.0},
        {1.0, -2.0},
    }});
    
    EXPECT_EQ(m.at(0, 0), -3.0);
    EXPECT_EQ(m.at(0, 1), 5.0);
    EXPECT_EQ(m.at(1, 0), 1.0);
    EXPECT_EQ(m.at(1, 1), -2.0);
}

TEST(MatrixTest, EqualityTrueMatrix4x4) {
    rtlib::Matrix4x4 m1({{
        {1.0, 2.0, 3.0, 4.0},
        {5.5, 6.5, 7.5, 8.5},
        {9.0, 10.0, 11.0, 12.0},
        {13.5, 14.5, 15.5, 16.5}
    }});
    
    rtlib::Matrix4x4 m2({{
        {1.0, 2.0, 3.0, 4.0},
        {5.5, 6.5, 7.5, 8.5},
        {9.0, 10.0, 11.0, 12.0},
        {13.5, 14.5, 15.5, 16.5}
    }});
    
    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, InequalityTrueMatrix4x4) {
    rtlib::Matrix4x4 m1({{
        {1.0, 2.0, 3.0, 4.0},
        {5.5, 6.5, 7.5, 8.5},
        {9.0, 10.0, 11.0, 12.0},
        {13.5, 14.5, 15.5, 16.5}
    }});
    
    rtlib::Matrix4x4 m2({{
        {1.0, 2.0, 3.0, 4.0},
        {5.5, 2.0, 7.5, 8.5},
        {9.0, 10.0, 11.0, 12.0},
        {13.5, 14.5, 15.5, 16.5}
    }});
    
    EXPECT_NE(m1, m2);
}

}
