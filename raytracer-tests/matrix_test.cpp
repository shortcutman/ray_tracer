//
//  matrix_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 23/12/2022.
//

#include <gtest/gtest.h>

#include "matrix.hpp"
#include "tuple.hpp"

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

TEST(MatrixTest, EqualityMatrix4x4) {
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

TEST(MatrixTest, InequalityMatrix4x4) {
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

TEST(MatrixTest, MultiplyMatrix4x4) {
    rtlib::Matrix4x4 m1({{
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 8.0, 7.0, 6.0},
        {5.0, 4.0, 3.0, 2.0}
    }});
    
    rtlib::Matrix4x4 m2({{
        {-2.0, 1.0, 2.0, 3.0},
        {3.0, 2.0, 1.0, -1.0},
        {4.0, 3.0, 6.0, 5.0},
        {1.0, 2.0, 7.0, 8.0}
    }});
    
    rtlib::Matrix4x4 result({{
        {20.0, 22.0, 50.0, 48.0},
        {44.0, 54.0, 114.0, 108.0},
        {40.0, 58.0, 110.0, 102.0},
        {16.0, 26.0, 46.0, 42.0}
    }});
    
    EXPECT_EQ(m1 * m2, result);
    
    auto m3 = m1;
    m3 *= m2;
    EXPECT_EQ(m3, result);
}

TEST(MatrixTest, MultiplyMatrix4x4AndTuple) {
    rtlib::Matrix4x4 m1({{
        {1.0, 2.0, 3.0, 4.0},
        {2.0, 4.0, 4.0, 2.0},
        {8.0, 6.0, 4.0, 1.0},
        {0.0, 0.0, 0.0, 1.0}
    }});
    
    rtlib::Tuple t1(1.0, 2.0, 3.0, 1.0);
    rtlib::Tuple result(18.0, 24.0, 33.0, 1.0);

    EXPECT_EQ(m1 * t1, result);
}


}
