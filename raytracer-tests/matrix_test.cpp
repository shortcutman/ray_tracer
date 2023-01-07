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

TEST(MatrixTest, IdentityMatrix2x2) {
    rtlib::Matrix2x2 identity2x2Result({{
        {1.0, 0.0},
        {0.0, 1.0}
    }});
    
    auto identityMatrix = rtlib::Matrix<2>::identityMatrix();
    EXPECT_EQ(identityMatrix, identity2x2Result);
}

TEST(MatrixTest, IdentityMatrix3x3) {
    rtlib::Matrix3x3 identity3x3Result({{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    }});
    
    auto identityMatrix = rtlib::Matrix<3>::identityMatrix();
    EXPECT_EQ(identityMatrix, identity3x3Result);
}

TEST(MatrixTest, IdentityMatrix4x4) {
    rtlib::Matrix4x4 identity4x4Result({{
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    }});
    
    auto identityMatrix = rtlib::Matrix<4>::identityMatrix();
    EXPECT_EQ(identityMatrix, identity4x4Result);
}

TEST(MatrixTest, MultiplyMatrix4x4AndIdentity) {
    rtlib::Matrix4x4 m({{
        {1.0, 2.0, 3.0, 4.0},
        {2.0, 4.0, 4.0, 2.0},
        {8.0, 6.0, 4.0, 1.0},
        {0.0, 0.0, 0.0, 1.0}
    }});
    
    EXPECT_EQ(m * rtlib::Matrix4x4::identityMatrix(), m);
}

TEST(MatrixTest, TransposeMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {0.0, 9.0, 3.0, 0.0},
        {9.0, 8.0, 0.0, 8.0},
        {1.0, 8.0, 5.0, 3.0},
        {0.0, 0.0, 5.0, 8.0}
    }});
    
    rtlib::Matrix4x4 r({{
        {0.0, 9.0, 1.0, 0.0},
        {9.0, 8.0, 8.0, 0.0},
        {3.0, 0.0, 5.0, 5.0},
        {0.0, 8.0, 3.0, 8.0}
    }});
    
    EXPECT_EQ(m.transpose(), r);
}

TEST(MatrixTest, TransposeIdentityMatrix) {
    EXPECT_EQ(rtlib::Matrix2x2::identityMatrix().transpose(),
              rtlib::Matrix2x2::identityMatrix());
    
    EXPECT_EQ(rtlib::Matrix3x3::identityMatrix().transpose(),
              rtlib::Matrix3x3::identityMatrix());
    
    EXPECT_EQ(rtlib::Matrix4x4::identityMatrix().transpose(),
              rtlib::Matrix4x4::identityMatrix());
}

TEST(MatrixTest, DeterminantMatrix2x2) {
    rtlib::Matrix2x2 m({{
        {1.0, 5.0},
        {-3.0, 2.0}
    }});
    
    EXPECT_EQ(m.determinant(), 17);
}

TEST(MatrixTest, SubmatrixOfMatrix3x3) {
    rtlib::Matrix3x3 m({{
        {1.0, 5.0, 0.0},
        {-3.0, 2.0, 7.0},
        {0.0, 6.0, -3.0}
    }});
    
    rtlib::Matrix2x2 r({{
        {-3.0, 2.0},
        {0.0, 6.0}
    }});
    
    EXPECT_EQ(m.submatrix(0, 2), r);
}

TEST(MatrixTest, SubmatrixOfMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {-6.0, 1.0, 1.0, 6.0},
        {-8.0, 5.0, 8.0, 6.0},
        {-1.0, 0.0, 8.0, 2.0},
        {-7.0, 1.0, -1.0, 1.0}
    }});
    
    rtlib::Matrix3x3 r({{
        {-6.0, 1.0, 6.0},
        {-8.0, 8.0, 6.0},
        {-7.0, -1.0, 1.0}
    }});
    
    EXPECT_EQ(m.submatrix(2, 1), r);
}

TEST(MatrixTest, MinorOfMatrix3x3) {
    rtlib::Matrix3x3 m({{
        {3.0, 5.0, 0.0},
        {2.0, -1.0, -7.0},
        {6.0, -1.0, 5.0}
    }});
    
    auto submatrix = m.submatrix(1, 0);
    
    EXPECT_EQ(submatrix.determinant(), 25);
    EXPECT_EQ(m.minor(1, 0), 25);
}

}
