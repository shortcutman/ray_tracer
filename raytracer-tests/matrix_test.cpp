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
    
    auto identityMatrix = rtlib::Matrix2x2::identityMatrix();
    EXPECT_EQ(identityMatrix, identity2x2Result);
}

TEST(MatrixTest, IdentityMatrix3x3) {
    rtlib::Matrix3x3 identity3x3Result({{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    }});
    
    auto identityMatrix = rtlib::Matrix3x3::identityMatrix();
    EXPECT_EQ(identityMatrix, identity3x3Result);
}

TEST(MatrixTest, IdentityMatrix4x4) {
    rtlib::Matrix4x4 identity4x4Result({{
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    }});
    
    auto identityMatrix = rtlib::Matrix4x4::identityMatrix();
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

TEST(MatrixTest, DeterminantMatrix3x3) {
    rtlib::Matrix3x3 m({{
        {1.0, 2.0, 6.0},
        {-5.0, 8.0, -4.0},
        {2.0, 6.0, 4.0}
    }});
    
    EXPECT_EQ(m.cofactor(0, 0), 56);
    EXPECT_EQ(m.cofactor(0, 1), 12);
    EXPECT_EQ(m.cofactor(0, 2), -46);
    EXPECT_EQ(m.determinant(), -196);
}

TEST(MatrixTest, DeterminantMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {-2.0, -8.0, 3.0, 5.0},
        {-3.0, 1.0, 7.0, 3.0},
        {1.0, 2.0, -9.0, 6.0},
        {-6.0, 7.0, 7.0, -9.0}
    }});
    
    EXPECT_EQ(m.cofactor(0, 0), 690);
    EXPECT_EQ(m.cofactor(0, 1), 447);
    EXPECT_EQ(m.cofactor(0, 2), 210);
    EXPECT_EQ(m.cofactor(0, 3), 51);
    EXPECT_EQ(m.determinant(), -4071);
}

#ifndef MATRIX_SIMD

TEST(MatrixTest, SubmatrixOfMatrixRaw3x3) {
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

TEST(MatrixTest, SubmatrixOfMatrixRaw4x4) {
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

TEST(MatrixTest, MinorOfMatrixRaw3x3) {
    rtlib::Matrix3x3 m({{
        {3.0, 5.0, 0.0},
        {2.0, -1.0, -7.0},
        {6.0, -1.0, 5.0}
    }});
    
    auto submatrix = m.submatrix(1, 0);
    
    EXPECT_EQ(submatrix.determinant(), 25);
    EXPECT_EQ(m.minor(1, 0), 25);
}

#elifdef MATRIX_SIMD

TEST(MatrixTest, SubmatrixOfMatrixSimd3x3) {
    rtlib::Matrix3x3 m({{
        {1.0, 5.0, 0.0},
        {-3.0, 2.0, 7.0},
        {0.0, 6.0, -3.0}
    }});
    
    rtlib::Matrix2x2 r({{
        {-3.0, 2.0},
        {0.0, 6.0}
    }});
    
    EXPECT_EQ(rtlib::MatrixSimd2x2Double(m.submatrix<simd_double2x2, double>(0, 2)), r);
}

TEST(MatrixTest, SubmatrixOfMatrixSimd4x4) {
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
    
    EXPECT_EQ(rtlib::MatrixSimd3x3Double(m.submatrix<simd_double3x3, double>(2, 1)), r);
}

TEST(MatrixTest, MinorOfMatrixSimd3x3) {
    rtlib::Matrix3x3 m({{
        {3.0, 5.0, 0.0},
        {2.0, -1.0, -7.0},
        {6.0, -1.0, 5.0}
    }});
    
    auto submatrix = m.submatrix<simd_double2x2, double>(1, 0);
    
    EXPECT_EQ(submatrix.determinant(), 25);
    EXPECT_EQ(m.minor(1, 0), 25);
}

#endif

TEST(MatrixTest, CofactorOfMatrix3x3) {
    rtlib::Matrix3x3 m({{
        {3.0, 5.0, 0.0},
        {2.0, -1.0, -7.0},
        {6.0, -1.0, 5.0}
    }});
    
    EXPECT_EQ(m.minor(0, 0), -12);
    EXPECT_EQ(m.cofactor(0, 0), -12);
    EXPECT_EQ(m.minor(1, 0), 25);
    EXPECT_EQ(m.cofactor(1, 0), -25);
    EXPECT_EQ(m.cofactor(1, 1), 15);
}

TEST(MatrixTest, PositiveInvertabilityMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {6.0, 4.0, 4.0, 4.0},
        {5.0, 5.0, 7.0, 6.0},
        {4.0, -9.0, 3.0, -7.0},
        {9.0, 1.0, 7.0, -6.0}
    }});
    
    EXPECT_EQ(m.determinant(), -2120);
    EXPECT_EQ(m.invertible(), true);
}

TEST(MatrixTest, NegativeInvertabilityMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {-4.0, 2.0, -2.0, -3.0},
        {9.0, 6.0, 2.0, 6.0},
        {0.0, -5.0, 1.0, -5.0},
        {0.0, 0.0, 0.0, 0.0}
    }});
    
    EXPECT_EQ(m.determinant(), 0);
    EXPECT_EQ(m.invertible(), false);
}

TEST(MatrixTest, InverseMatrix4x4) {
    rtlib::Matrix4x4 m({{
        {-5.0, 2.0, 6.0, -8.0},
        {1.0, -5.0, 1.0, 8.0},
        {7.0, 7.0, -6.0, -7.0},
        {1.0, -3.0, 7.0, 4.0}
    }});
    
    auto inverse = m.inverse();
    
    EXPECT_EQ(m.determinant(), 532);
    EXPECT_EQ(m.cofactor(2, 3), -160);
    EXPECT_EQ(m.cofactor(3, 2), 105);
    
    rtlib::Matrix4x4 inverseResult({{
        { 0.2180450 ,  0.451128 ,  0.2406020 , -0.0451128 } ,
        {-0.8082710 , -1.456770 , -0.4436090 ,  0.5206770},
        {-0.0789474 , -0.223684 , -0.0526316 ,  0.1973680},
        {-0.5225560 , -0.813910 , -0.3007520 ,  0.3063910}
    }});
        
    EXPECT_EQ(inverseResult, inverse);
}

TEST(MatrixTest, InverseMatrix4x4No2) {
    rtlib::Matrix4x4 m({{
        {8.0, -5.0, 9.0, 2.0},
        {7.0, 5.0, 6.0, 1.0},
        {-6.0, 0.0, 9.0, 6.0},
        {-3.0, 0.0, -9.0, -4.0}
    }});
    
    auto inverse = m.inverse();
    
    rtlib::Matrix4x4 inverseResult({{
        {-0.153846, -0.153846, -0.282051, -0.538462},
        {-0.0769231, 0.123077, 0.025641, 0.0307692},
        {0.358974, 0.358974, 0.435897, 0.923077},
        {-0.692308, -0.692308, -0.769231, -1.92308}
    }});
        
    EXPECT_EQ(inverseResult, inverse);
}

TEST(MatrixTest, InverseMatrix4x4No3) {
    rtlib::Matrix4x4 m({{
        {9.0, 3.0, 0.0, 9.0},
        {-5.0, -2.0, -6.0, -3.0},
        {-4.0, 9.0, 6.0, 4.0},
        {-7.0, 6.0, 6.0, 2.0}
    }});
    
    auto inverse = m.inverse();
    
    rtlib::Matrix4x4 inverseResult({{
        {-0.0407407, -0.0777778, 0.144444, -0.222222},
        {-0.0777778, 0.0333333, 0.366667, -0.333333},
        {-0.0290123, -0.146296, -0.109259, 0.12963},
        {0.177778, 0.0666667, -0.266667, 0.333333}
    }});
        
    EXPECT_EQ(inverseResult, inverse);
}

TEST(MatrixTest, MultiplyingProductByInverseToGetOriginalResult) {
    rtlib::Matrix4x4 m1({{
        {3.0, -9.0, 7.0, 3.0},
        {3.0, -8.0, 2.0, -9.0},
        {-4.0, 4.0, 4.0, 1.0},
        {-6.0, 5.0, -1.0, 1.0}
    }});
    
    rtlib::Matrix4x4 m2({{
        {8.0, 2.0, 2.0, 2.0},
        {3.0, -1.0, 7.0, 0.0},
        {7.0, 0.0, 5.0, 4.0},
        {6.0, -2.0, 0.0, 5.0}
    }});
    
    auto multiplyResult = m1 * m2;
    EXPECT_EQ(m1, multiplyResult * m2.inverse());
}

}
